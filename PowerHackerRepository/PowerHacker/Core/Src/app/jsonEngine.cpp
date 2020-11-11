/*
 * jsonEngine.cpp
 *
 *  Created on: 11 nov. 2020
 *      Author: Javier
 */


#include <jsonEngine.hpp>

const int staticCapacity = JSON_OBJECT_SIZE(4);

DeserializationError jsonEngine::parseInstruction(const string &jsoninstruction, instructionChunk_t &instructionChunk){
	StaticJsonDocument<staticCapacity> doc;
	DeserializationError err = deserializeJson(doc, jsoninstruction);

	if(!err){
		instructionChunk.message = doc["message"].as<string>();
		instructionChunk.value = doc["value"].as<double>();
	}

	return err;
}
