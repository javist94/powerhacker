/*
 * serialInterfaces.h
 *
 *  Created on: Nov 8, 2020
 *      Author: javier
 */

#ifndef SRC_APP_SERIALINTERFACES_H_
#define SRC_APP_SERIALINTERFACES_H_

#define MAX_RXBUFF_SIZE 128

#include <usbd_cdc_if.h>
#include <string>
#include "../Lib/FIFO.h"

class serialInterface{
public:
	virtual uint8_t sendString(std::string const &sendstr) = 0; //Slow method (internal memory copy), but quick to test
	virtual std::string readChar() = 0;
	virtual std::string readUntil(char endchar, unsigned short timeout);

protected:
	serialInterface() {};
};


class USBInterface : public serialInterface{
public:
	uint8_t sendStr(std::string const &sendstr);
	std::string readChar();
	std::string readUntil(char endchar, unsigned short timeout);
};


#endif /* SRC_APP_SERIALINTERFACES_H_ */
