#include <boardUserInterface.hpp>

bool boardUserInterface::anyButtonPressed(){
	this->readButtons();
	bool isAnyButtonPressed = false;
	if(this->countPressed() > 0) isAnyButtonPressed = true;
	return isAnyButtonPressed;
}

boardUserInterface::boardUserInterface(){
	this->readButtons();
}

int boardUserInterface::getButtonCount(){
	this->readButtons();
	return (int)this->countPressed();
}

buttonTree boardUserInterface::getPressedButtons(){
	buttonTree pressedButtons;
	this->readButtons();
	pressedButtons.modeButton = modeBtn;
	pressedButtons.selectButton = selectBtn;
	pressedButtons.toggleButton = toggleBtn;
	return pressedButtons;
}

void boardUserInterface::readButtons(){
	this->modeBtn = false; this->selectBtn = false; this->toggleBtn = false;
	if(HAL_GPIO_ReadPin(GPIOB, BUTTON_MODE_Pin) == false) this->modeBtn = true;
	if(HAL_GPIO_ReadPin(GPIOA, BUTTON_CHSELECT_Pin) == false) this->selectBtn = true;
	if(HAL_GPIO_ReadPin(GPIOA, BUTTON_CHENABLE_Pin) == false) this->toggleBtn = true;
}

unsigned char boardUserInterface::countPressed(){
	unsigned char buttonCount = 0;
	if(modeBtn) buttonCount++;
	if(selectBtn) buttonCount++;
	if(toggleBtn) buttonCount++;
	return buttonCount;
}

ledIndicator::ledIndicator(GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin){
	this->_GPIO_Pin = GPIO_Pin;
	this->_GPIO_Port = GPIO_Port;
}

void ledIndicator::setState(ledState state){
	if(this->_status != state){
		switch(state){
				case ledState::on:
					HAL_GPIO_WritePin(this->_GPIO_Port, this->_GPIO_Pin, GPIO_PIN_SET);
					this->_status = ledState::on;
					break;
				case ledState::off:
					HAL_GPIO_WritePin(this->_GPIO_Port, this->_GPIO_Pin, GPIO_PIN_RESET);
					this->_status = ledState::off;
					break;
				case ledState::toggle:
					HAL_GPIO_TogglePin(this->_GPIO_Port, this->_GPIO_Pin);
					if(this->_status == ledState::on) this->_status = ledState::off; else this->_status = ledState::on;
					break;
		}
	}
}
