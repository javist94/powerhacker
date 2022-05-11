/*
 * serialInterfaces.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: javier
 */

#include <serialInterfaces.hpp>

/* Create FIFO and flag*/
volatile fifo_t fifo_rx = fifo_create(MAX_RXBUFF_SIZE, sizeof(char));
volatile uint8_t RX_FLAG = 0;

uint8_t USBInterface::sendString(std::string const &sendstr){
	uint8_t result = USBD_OK;
	uint8_t* buffer = (uint8_t*)sendstr.c_str();
	uint32_t buffsize = sendstr.length();
	result = CDC_Transmit_FS(buffer, buffsize);
	return result;
}

std::string USBInterface::readChar(){
	char buffer_cstr[MAX_RXBUFF_SIZE] = {0};
	volatile uint8_t i = 0;
	char c = '0';

	while (!fifo_is_empty(fifo_rx)) {
		fifo_get(fifo_rx, &c);
		buffer_cstr[i] = c;
		i++;
	}

	RX_FLAG = 0;
	std::string result(buffer_cstr);
	return result;
}


//Timeout in milliseconds, 100ms by default
std::string USBInterface::readUntil(char endchar, unsigned short timeout){
	char buffer_cstr[MAX_RXBUFF_SIZE] = {0};
	volatile uint8_t i = 0;
	char c = '0';
	bool op_timeout = false;
	std::string result = "";
	uint32_t initial_time = HAL_GetTick();

	while (c != endchar && !op_timeout)
	{
		if(!fifo_is_empty(fifo_rx)){
			fifo_get(fifo_rx, &c);
			buffer_cstr[i] = c;
			initial_time = HAL_GetTick();
			i++;
		}else{
			if(HAL_GetTick() - initial_time > timeout) op_timeout = true;
		}
	}

	RX_FLAG = 0;

	if(op_timeout){
		result.clear();
		result = "{'error' : 'rx_timeout'}\n";
	}else{
		result.clear();
		result.insert(0, buffer_cstr);
	}

	return result;
}
