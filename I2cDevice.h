#ifndef I2CDEVICE
#define I2CDEVICE

#include "Arduino.h"

class I2cDevice{
protected:
	bool ready = false;
	uint8_t deviceAddress;

	void writeRegister(uint8_t reg,uint8_t val);
	uint8_t readRegister(uint8_t reg);
public:
	I2cDevice(uint8_t address);
	bool isReady();
};

#endif