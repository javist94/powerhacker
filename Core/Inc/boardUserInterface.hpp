/*
 * uiAbstractionLayerDef.hpp
 *
 *  Created on: Nov 5, 2020
 *      Author: javier
 */

#ifndef INC_BOARDUSERINTERFACE_HPP_
#define INC_BOARDUSERINTERFACE_HPP_

#include <main.h>

//Definitions
struct buttonTree{
	bool modeButton = false, selectButton = false, toggleButton = false;
};

struct ledTree{
	bool sdLed = false, runLed = false, ch1led = false, ch2led = false;
};

enum class ledState {
	off, on, toggle
};

class ledIndicator{
public:
	ledIndicator(GPIO_TypeDef*, uint16_t);
	ledState getState() { return _status; }
	void setState(ledState state);
private:
	ledState _status = ledState::off;
	uint16_t _GPIO_Pin;
	GPIO_TypeDef* _GPIO_Port;
};

class boardUserInterface{
public:
	boardUserInterface();
	//Buttons
	bool anyButtonPressed();
	int getButtonCount();
	buttonTree getPressedButtons();
	//LEDs
	ledIndicator sdLed = {GPIOF, SDCARD_LOG_LED_Pin};
	ledIndicator runLed = {GPIOF, SDCARD_SCRIPT_LED_Pin};
	ledIndicator ch1Led = {GPIOB, LOAD_CH1_LED_Pin};
	ledIndicator ch2Led = {GPIOB, LOAD_CH2_LED_Pin};

private:
	unsigned char countPressed();
	void readButtons();
	bool modeBtn, toggleBtn, selectBtn;
};


#endif /* INC_BOARDUSERINTERFACE_HPP_ */
