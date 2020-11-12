/*
 * jsonEngine.hpp
 *
 *  Created on: 11 nov. 2020
 *      Author: Javier
 */

#ifndef INC_JSONENGINE_HPP_
#define INC_JSONENGINE_HPP_

#include <../Lib/json/arduino_json.h>
#include <masterController.hpp>
#include <PowerManager.hpp>
#include <serialInterfaces.hpp>
#include <string>

using namespace std;

enum class instructionType_e{
	voltageSet, voltageGet, currentSet, currentGet, modeControl, error, warning, info, other, unknown
};

struct instructionChunk_t{
	instructionType_e instructionType;
	double value;
	string message;
	channel_e channel;
};

class jsonEngine{
public:
	DeserializationError parseInstruction(const string &jsoninstruction, instructionChunk_t &instructionChunk);
	string getACKPacket();
	string getErrPacket(const string &errmsg);
};

#endif /* INC_JSONENGINE_HPP_ */
