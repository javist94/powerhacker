/*
 * jsonEngine.cpp
 *
 *  Created on: 11 nov. 2020
 *      Author: Javier
 */


#include <jsonEngine.hpp>

const int staticCapacity = JSON_OBJECT_SIZE(512);

DeserializationError jsonEngine::parseInstruction(const string &jsoninstruction, instructionChunk_t &instructionChunk){

	StaticJsonDocument<staticCapacity> doc;
	DeserializationError err = deserializeJson(doc, jsoninstruction);

	if(err == DeserializationError::Ok){

		instructionChunk.message = doc["message"].as<string>();
		instructionChunk.value = doc["value"].as<double>();

		string channel = doc["channel"].as<string>();
			if(channel == "ch1") instructionChunk.channel = channel_e::ch1;
			else if(channel == "ch2") instructionChunk.channel = channel_e::ch2;
			else instructionChunk.channel = channel_e::ch1; //ch1 if channel is not specified

		string msgtype = doc["type"].as<string>();
			if(msgtype == "vset") instructionChunk.instructionType = instructionType_e::voltageSet;
			else if(msgtype == "vget") instructionChunk.instructionType = instructionType_e::voltageGet;
			else if(msgtype == "cset") instructionChunk.instructionType = instructionType_e::currentSet;
			else if(msgtype == "cget") instructionChunk.instructionType = instructionType_e::currentGet;
			else if(msgtype == "mode") instructionChunk.instructionType = instructionType_e::modeControl;
			else if(msgtype == "error")instructionChunk.instructionType = instructionType_e::error;
			else if(msgtype == "warning")instructionChunk.instructionType = instructionType_e::warning;
			else if(msgtype == "info") instructionChunk.instructionType = instructionType_e::info;
			else if(msgtype == "other")instructionChunk.instructionType = instructionType_e::other;
			else instructionChunk.instructionType = instructionType_e::unknown;

	}

	return err;
}

string jsonEngine::getErrPacket(const string &errmsg){
	string result;
	StaticJsonDocument<JSON_OBJECT_SIZE(128)> err;
	err["type"] = "error";
	err["message"] = errmsg;
	serializeJson(err, result);
	return result + "\n";
}

string jsonEngine::getACKPacket(){
	string result;
	StaticJsonDocument<JSON_OBJECT_SIZE(30)> ack;
	ack["type"] = "info";
	ack["message"] = "acknowledge";
	serializeJson(ack, result);
	return result + "\n";
}
