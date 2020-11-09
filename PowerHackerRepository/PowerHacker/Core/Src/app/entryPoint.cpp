/*
 * powerhacker.cpp
 *
 *  Created on: Nov 5, 2020
 *      Author: javier
 */

//Main files header, auto-generated, and STM32 C libraries
#include <main.h>

//C++ Standard library
#include <string>

//C++ Application libraries
#include <entryPointDefinition.hpp>
#include <boardUserInterface.hpp>
#include <masterController.hpp>
#include <serialInterfaces.hpp>


boardUserInterface boardUI;
masterController masterControl;
USBInterface usbController;

extern DAC_HandleTypeDef hdac1, hdac2;
extern FIFO RX_FIFO;

uint32_t dac_value = 0;

void entryPointSetup(){
	// Initialize some peripherals
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	// Check if select is pressed on startup to execute calibration routine
}

void setDAC(DAC_HandleTypeDef *handle){
	HAL_DAC_SetValue(handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
}

unsigned short readSDADC(SDADC_HandleTypeDef *handle){
	//TODO: implement SDADC read function, returns ushort (16 bits, positive)
	return (short)0;
}



void entryPointLoop(){
	captureUserInput();
	if(RX_FIFO.rx_flag == 1){
		usbController.sendStr(usbController.receiveStr());
		boardUI.runLed.setState(ledState::on);
	}else{
		boardUI.runLed.setState(ledState::off);
	}
}

void captureUserInput(){
	if(boardUI.anyButtonPressed()){
		buttonTree pressedBtns = boardUI.getPressedButtons();
		masterControl.digestUI(pressedBtns);
		std::string test = "<'Mode' Button Pressed>\n";
		usbController.sendStr(test);
		HAL_Delay(200);
	}

}
