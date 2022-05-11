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

enum class channel_e {
	 ch1 = 1, ch2 = 2
};

class powerChannel{
public:
	powerChannel(string const &name) {this->_name = name;};
	void init(SDADC_HandleTypeDef *sdadcHandleVRead, SDADC_HandleTypeDef *sdadcHandleCRead, \
	 DAC_HandleTypeDef *dacHandle, const uint32_t vReadChannel, const uint32_t cReadChannel, \
	 const uint32_t DACCHANNEL);
	void setVoltage(double voltage);
	void setCurrent();
	float readVoltage();
	float readCurrent();
	bool channelIsReady() { return _chready; }

private:
	bool _chready = false;
	//C Handles
	SDADC_HandleTypeDef* _sdadcHandleVRead;
	SDADC_HandleTypeDef* _sdadcHandleCRead;
	DAC_HandleTypeDef* _dacHandle;

	//Channels
	uint32_t _vSDADCChannel = 0, _cSDADCChannel = 0, _DACChannel = 0;
	
	//Internal class status
	string _name = "";
	uint32_t _dacSteps = 0, _cSdadcSteps = 0, _vSdadcSteps = 0;
	powerMode_t powerMode = powerMode_t::notSet;
	float _currentSetPoint = 0.0f, _voltageSetPoint = 0.0f;

	//Methods
	uint32_t _vSDADCRead(), _cSDADCRead();
	void _dacSet(uint32_t dacSteps);
};

class PowerManager {
public:
	powerChannel channel1 = {"Channel 1"}, channel2 = {"Channel 2"};
};

#endif /* SRC_APP_POWERMANAGER_H_ */
