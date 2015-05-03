#include "Accelerometer.h"

Accelerometer::Accelerometer(): I2cDevice(LSM303_ADDRESS_ACC){
	//enable accelerometer at 400hz
	writeRegister(LSM303_REGISTER_ACCEL_CTRL_REG1_A,0x77);
	digitalWriteFast(13,HIGH);
	//assume its all good
	//uint8_t reg1_a = readRegister(LSM303_REGISTER_ACCEL_CTRL_REG1_A);
	//DEBUGSPRINTLN((reg1_a,HEX));

	xOffset = 0;
	yOffset = 0;
	zOffset = 0;

	ready = true;
}

//handle errors here!!
void Accelerometer::update(){
	Wire.beginTransmission(deviceAddress);
	Wire.write(LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80);
	Wire.endTransmission();

	Wire.requestFrom(deviceAddress,6);
	while(Wire.available() < 6);
	x = (Wire.read() | Wire.read() << 8) - xOffset;
	y = (Wire.read() | Wire.read() << 8) - yOffset;
	z = (Wire.read() | Wire.read() << 8) - zOffset;

	Wire.endTransmission();
}

void Accelerometer::calibrateOffset(){
	DEBUGSPRINTLN("accelerometer calibration not implemented");
}