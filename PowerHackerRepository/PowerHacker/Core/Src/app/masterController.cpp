/*
 * boardState.cpp
 *
 *  Created on: Nov 5, 2020
 *      Author: javier
 */

#include <masterController.hpp>
#include <serialInterfaces.hpp>
#include <jsonEngine.hpp>
#include <powerManager.hpp>

extern PowerManager powerManager;
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
		//TODO: check cmd is correct // EXAMPLE: {"type" : "vset", "channel" : "ch1", "value": 2.4}
		DeserializationError err;
		err = jsonEngineRunner.parseInstruction(cmd, ichunk);

		if(!err)
		{
			//Send ACK to show that the JSON string was received and parsed without errors
			usbController.sendString(jsonEngineRunner.getACKPacket());
			//Decide what to do depending on ichunk
			if(ichunk.instructionType == instructionType_e::voltageSet){
				usbController.sendString("VSET: " + std::to_string(ichunk.value) + "\n" + "CH: " + std::to_string(static_cast<int>(ichunk.channel)));
				if(ichunk.channel == channel_e::ch1) powerManager.channel1.setVoltage(ichunk.value);
				else if(ichunk.channel == channel_e::ch2) powerManager.channel2.setVoltage(ichunk.value);
			}
		}else{
			//Parsing error, send back the error in JSON format
			usbController.sendString(jsonEngineRunner.getErrPacket(string(err.c_str())));
		}

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
