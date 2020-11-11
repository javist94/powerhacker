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
#include <serialInterfaces.hpp>
#include <string>

using namespace std;

enum class instructionType_e{
	voltageSet, voltageGet, currentSet, currentGet, modeControl, message
};

struct instructionChunk_t{
	instructionType_e instructionType;
	double value;
	string message;
	runStatus rstatus;
};

class jsonEngine{
public:
	DeserializationError parseInstruction(const string &jsoninstruction, instructionChunk_t &instructionChunk);

};

#endif /* INC_JSONENGINE_HPP_ */
