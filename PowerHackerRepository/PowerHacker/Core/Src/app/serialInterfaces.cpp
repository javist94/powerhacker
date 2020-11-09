/*
 * serialInterfaces.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: javier
 */

#include <serialInterfaces.hpp>

/* Create FIFO*/
FIFO RX_FIFO = {.rx_flag=0, .head=0, .tail=0};

uint8_t USBInterface::sendStr(std::string const &sendstr){
	uint8_t result = USBD_OK;
	uint8_t* buffer = (uint8_t*)sendstr.c_str();
	uint32_t buffsize = sendstr.length() + 1; //Account for the null-terminated character
	result = CDC_Transmit_FS(buffer, buffsize);
	return result;
}

std::string USBInterface::receiveStr(){
	uint8_t Len = MAX_RXBUFF_SIZE;
	uint8_t buffer[MAX_RXBUFF_SIZE];
	uint8_t* pbuff = buffer;

	uint32_t count=0;
	/* Check inputs */
	  if ((pbuff == NULL) || (Len == 0))
	 {
	  return "";
	 }

	while (Len > 0)
	{
		Len--;
		if (RX_FIFO.head==RX_FIFO.tail) return "";
		count++;
		*pbuff++=RX_FIFO.data[RX_FIFO.tail];
		RX_FIFO.tail=FIFO_INCR(RX_FIFO.tail);
	}

	RX_FIFO.rx_flag = 0;
	std::string result((char*)buffer);
	return result;
}
