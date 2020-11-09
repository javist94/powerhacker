/*
 * powerManager.h
 *
 *  Created on: Nov 9, 2020
 *      Author: javier
 */

#ifndef SRC_APP_POWERMANAGER_H_
#define SRC_APP_POWERMANAGER_H_

#include <main.h>
#include <string>

using namespace std;

enum class powerMode_t{
	currentSet, voltageSet, notSet
};

class powerChannel{
public:
	powerChannel(SDADC_HandleTypeDef *sdadcHandle, DAC_HandleTypeDef *dacHandle, string const &name) {this->_name = name;};
	void setVoltage();
	void setCurrent();
	float readVoltage();
	float readCurrent();
private:
	SDADC_HandleTypeDef* _sdadcHandle;
	DAC_HandleTypeDef* _dacHandle;
	string _name = "";
	short _dacSteps = 0;
	int _sdadcSteps = 0;
	powerMode_t powerMode = powerMode_t::notSet;
	float _currentSetPoint = 0.0f, _voltageSetPoint = 0.0f;
	int rawReadSDADCSteps();
	void rawWriteDACSteps(short dacSteps);
};

class powerManager {
public:
	//powerChannel channel1 = {"Channel 1"}, channel2 = {"Channel 2"};

};

#endif /* SRC_APP_POWERMANAGER_H_ */
