#include "Barometer.h"

Barometer::Barometer(): I2cDevice(BMP180_ADDRESS){
	//enable accelerometer at 400hz
	DEBUGSPRINTLN("barometer not implemented");

	ready = false;
}

//handle errors here!!
void Barometer::update(){
	DEBUGSPRINTLN("barometer updating not implemented");
}

void Barometer::calibrateOffset(){
	DEBUGSPRINTLN("barometer calibration not implemented");
}