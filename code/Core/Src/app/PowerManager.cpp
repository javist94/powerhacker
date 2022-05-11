/*
 * powerManager.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: javier
 */

#include "main.h"
#include <cmath>
#include <powerManager.hpp>
#include <jsonEngine.hpp>

extern SDADC_HandleTypeDef hsdadc1;
extern SDADC_HandleTypeDef hsdadc2;
extern SDADC_HandleTypeDef hsdadc3;
extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac2;

extern PowerManager powerManager;
extern USBInterface usbController;
extern jsonEngine jsonEngineRunner;

void powerChannel::setVoltage(double voltage){
	/*
	 * 0: Check voltage is positive
	 * 1: Check that voltage is reachable with current power input
	 * 2: Calculate approximate DAC steps
	 * 3: Implement PID until desired value is reached at the output
	 */
	if(voltage < 0) {
		//Error v < 0
		usbController.sendString(jsonEngineRunner.getErrPacket(string("Voltage cannot be inferior to zero!")));
	}else{
		uint32_t targetSteps = std::floor((voltage / 3.3f) * 4095);
		this->_dacSet(targetSteps);
	}
}

void powerChannel::_dacSet(uint32_t steps){
	//DAC is 12 bits
	if(steps < 0 || steps > 4095) return; //Invalid input
	
	if(!this->_chready) { //Channel has not been initialised: print error and return
		usbController.sendString(jsonEngineRunner.getErrPacket(string("Channel not initialised. Please initialise the channel before attempting to use it.")));
		return;
	}

	HAL_DAC_SetValue(this->_dacHandle, this->_DACChannel, DAC_ALIGN_12B_R, steps);

	//DEBUG
	std::string debug_steps_str = "DAC STEPS: ";
	debug_steps_str.append(std::to_string(steps));
	debug_steps_str.append("\n");
	usbController.sendString(debug_steps_str);
}

void powerChannel::init(SDADC_HandleTypeDef *sdadcHandleVRead, SDADC_HandleTypeDef *sdadcHandleCRead, \
 DAC_HandleTypeDef *dacHandle, const uint32_t vReadChannel, \
 const uint32_t cReadChannel, const uint32_t DACChannel) {
	//Store the information: handles
	this->_dacHandle = dacHandle;
	this->_sdadcHandleVRead = sdadcHandleVRead;
	this->_sdadcHandleCRead = sdadcHandleCRead;
	//Store the channels for each STM32 peripheral
	this->_DACChannel = DACChannel;
	this->_vSDADCChannel = vReadChannel;
	this->_cSDADCChannel = cReadChannel;

	//Cal HAL library startup routine for low level operations on the STM32
	HAL_DAC_Start(dacHandle, DACChannel);
	HAL_SDADC_Start(sdadcHandleVRead);
	HAL_SDADC_Start(sdadcHandleCRead);

	//Set its state to true
	this->_chready = true;
}

