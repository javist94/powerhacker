/*
 * boardState.cpp
 *
 *  Created on: Nov 5, 2020
 *      Author: javier
 */

#include <masterController.hpp>
#include <serialInterfaces.hpp>
#include <jsonEngine.hpp>

extern boardUserInterface boardUI;
extern USBInterface usbController;
extern jsonEngine jsonEngineRunner;
extern uint8_t RX_FLAG;

masterController::masterController(){
	//No constructor (deprecated)
}

void masterController::digestUSB(){
	if(RX_FLAG == 1){ //Check we can read
		std::string cmd;
		cmd = usbController.readUntil('\n');
		instructionChunk_t ichunk;
		//TODO: check cmd is correct

		//Parse JSON and store info into ichunk
		jsonEngineRunner.parseInstruction(cmd, ichunk);

		//Decide what to do depending on ichunk
		// ¿External void?
	}
}

void masterController::digestUI(buttonTree btntree){
	switch(this->currentState_){
		case runStatus::directControl:
			if(btntree.toggleButton){
				this->rotateChannel();
			}
			break;
		case runStatus::scriptExec:
			/*TODO: if mode pressed: stop script --> directControl
			 * any other button, expose it to the script sequence being executed
			 */
			break;

		case runStatus::serialControl:
			//Send that user requested to stop, ask for confirmation
			break;
	}
}

void masterController::rotateChannel(){
	if(boardUI.ch1Led.getState() == ledState::off && boardUI.ch2Led.getState() == ledState::off){
						boardUI.ch1Led.setState(ledState::on);
						boardUI.ch2Led.setState(ledState::off);
				}else if(boardUI.ch1Led.getState() == ledState::on && boardUI.ch2Led.getState() == ledState::off){
						boardUI.ch1Led.setState(ledState::off);
						boardUI.ch2Led.setState(ledState::on);
				}else if(boardUI.ch1Led.getState() == ledState::off && boardUI.ch2Led.getState() == ledState::on){
						boardUI.ch1Led.setState(ledState::on);
						boardUI.ch2Led.setState(ledState::on);
				}else if(boardUI.ch1Led.getState() == ledState::on && boardUI.ch2Led.getState() == ledState::on){
						boardUI.ch1Led.setState(ledState::off);
						boardUI.ch2Led.setState(ledState::off);
	}
}
