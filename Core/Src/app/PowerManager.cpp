/*
 * powerManager.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: javier
 */

#include "main.h"
#include <powerManager.hpp>
#include <cmath>

extern SDADC_HandleTypeDef hsdadc1;
extern SDADC_HandleTypeDef hsdadc2;
extern SDADC_HandleTypeDef hsdadc3;
extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac2;
extern PowerManager powerManager;

void powerInit(){
//Channel 1 initialization
	powerManager.channel1.registerHandles(&hsdadc2, &hsdadc1, &hdac1);
}

void powerChannel::setVoltage(double voltage){
	/*
	 * 0: Check voltage is positive
	 * 1: Check that voltage is reachable with current power input
	 * 2: Calculate approximate DAC steps
	 * 3: Implement PID until desired value is reached at the output
	 */
	if(voltage < 0.0) return;
	const double mockInputVoltage = 4.7;
	short targetSteps = std::floor((voltage / mockInputVoltage) * 4095);
	this->setDACSteps(targetSteps);
}

void powerChannel::setDACSteps(short steps){
	//DAC is 12 bits
	if(steps < 0 || steps > 4095) return; //Invalid input
	HAL_DAC_SetValue(this->_dacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, steps);
}

void powerChannel::registerHandles(SDADC_HandleTypeDef *sdadcHandleVRead, SDADC_HandleTypeDef *sdadcHandleCRead, DAC_HandleTypeDef *dacHandle){
	this->_dacHandle = dacHandle;
	this->_sdadcHandleVRead = sdadcHandleVRead;
	this->_sdadcHandleCRead = sdadcHandleCRead;
	this->_chready = true;
}

