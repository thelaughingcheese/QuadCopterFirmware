#ifndef ACCELEROMETER
#define ACCELEROMETER

class Accelerometer{
	bool ready = false;

	void writeRegister(uint8_t reg,uint8_t val);
	uint8_t readRegister(uint8_t reg);
};

#endif