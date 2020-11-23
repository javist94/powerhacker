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
#include <PowerManager.hpp>
#include <serialInterfaces.hpp>
#include <jsonEngine.hpp>

PowerManager powerManager;
boardUserInterface boardUI;
masterController masterControl;
USBInterface usbController;
jsonEngine jsonEngineRunner;

extern SDADC_HandleTypeDef hsdadc1;
extern SDADC_HandleTypeDef hsdadc2;
extern SDADC_HandleTypeDef hsdadc3;
extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac2;
extern volatile uint8_t RX_FLAG;

extern void powerInit();

uint32_t dac_value = 0;

void entryPointSetup(){
	powerInit(); //Peripheral initialization
	//TODO: Check if select is pressed on startup to execute calibration routine

}

void entryPointLoop(){
	captureUserInput();
	masterControl.digestUSB();
}

void captureUserInput(){
	if(boardUI.anyButtonPressed()){
		buttonTree pressedBtns = boardUI.getPressedButtons();
		masterControl.digestUI(pressedBtns);
		HAL_Delay(200);
	}

}
