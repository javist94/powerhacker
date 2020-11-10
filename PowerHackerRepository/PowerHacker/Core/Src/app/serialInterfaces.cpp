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

uint8_t USBInterface::sendStr(std::string const &sendstr){
	uint8_t result = USBD_OK;
	uint8_t* buffer = (uint8_t*)sendstr.c_str();
	uint32_t buffsize = sendstr.length() + 1; //Account for the null-terminated character
	result = CDC_Transmit_FS(buffer, buffsize);
	return result;
}

std::string USBInterface::receiveStr(){
	if(!RX_FLAG) return "{'error' : 'Buffer was empty'}";

	char buffer_cstr[MAX_RXBUFF_SIZE] = {0};
	volatile uint8_t i = 0;
	char c;

	while (!fifo_is_empty(fifo_rx)) {
		fifo_get(fifo_rx, &c);
		buffer_cstr[i] = c;
		i++;
	}

	RX_FLAG = 0;
	std::string result(buffer_cstr);
	return result;
}

//Blocking function, waits until a full instruction has been received
std::string USBInterface::receiveInstruction(){
	std::string rxstr = "";
	while(!RX_FLAG); //Wait until something is received
	//Loop until string contains new line
	while(rxstr.find('\n') == std::string::npos){
		//New line not detected
		rxstr += this->receiveStr();
	}
	//We disable interrupts to avoid altering the FIFO register now
	__disable_irq();

	//New line detected, detect if it is NOT at the end
	if(rxstr.back() != '\n'){
		std::string remainder = "";
		//The character is not at the end, we need to put back the remainder in the FIFO
		unsigned short i = (unsigned short)0;
		i = rxstr.find('\n');
		remainder = rxstr.substr(i, rxstr.length()-1); //gets from '\n' onwards
		rxstr = rxstr.substr(0, i); //gets the useful part at this stage
		//Now we need to return the remainder to the FIFO from left to right
		for(unsigned short j = 0; j < remainder.length(); j++){
			fifo_add(fifo_rx, &remainder[j]);
		}
		//Now we trigger a signal for those characters to be read back in the following iteration
		RX_FLAG = 1;
	}

	__enable_irq(); //We enable back interrupts

	return rxstr;
}
