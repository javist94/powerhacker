/*
 * serialInterfaces.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: javier
 */

#include <serialInterfaces.hpp>

/* Create FIFO and flag*/
fifo_t fifo_rx = fifo_create(MAX_RXBUFF_SIZE, sizeof(char));
volatile uint8_t RX_FLAG = 0;

uint8_t USBInterface::sendStr(std::string const &sendstr){
	uint8_t result = USBD_OK;
	uint8_t* buffer = (uint8_t*)sendstr.c_str();
	uint32_t buffsize = sendstr.length() + 1; //Account for the null-terminated character
	result = CDC_Transmit_FS(buffer, buffsize);
	return result;
}

std::string USBInterface::receiveStr(){
	char buffer_cstr[MAX_RXBUFF_SIZE];
	uint8_t i = 0;

	while (!fifo_is_empty(fifo_rx)) {
		    char c;
		    fifo_get(fifo_rx, &c);
		    buffer_cstr[i] = c;
		    i++;
	}

	RX_FLAG = 0;
	std::string result(buffer_cstr);
	return result;
}
