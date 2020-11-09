/*
 * boardState.cpp
 *
 *  Created on: Nov 5, 2020
 *      Author: javier
 */

#include <masterController.hpp>

extern boardUserInterface boardUI;

masterController::masterController(){
	//No constructor (deprecated)
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
