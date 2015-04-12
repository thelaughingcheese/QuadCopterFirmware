#include "Gyroscope.h"

//configure
Gyroscope::Gyroscope(){
	//start wire
	Wire.begin();

	//check if device is correct
	uint8_t who = readRegister(GYRO_REGISTER_WHO_AM_I);
	if(who != 0xd7){
		DEBUGSPRINTLN("expecting gyroscope! invalid device");
		DEBUGSPRINTLN((who,HEX));
		ready = false;
		return;
	}

	//clear and set config reg 1
	writeRegister(GYRO_REGISTER_CTRL_REG1,0x00);
	writeRegister(GYRO_REGISTER_CTRL_REG1,0xff);

	//set config reg 4
	writeRegister(GYRO_REGISTER_CTRL_REG4,0x00);

	x=0;y=0;z=0;
	xOffset=0;yOffset=0;zOffset=0;

	ready = true;
}

void Gyroscope::writeRegister(uint8_t reg,uint8_t val){
	Wire.beginTransmission(L2GD20H_ADDRESS);
	Wire.write(reg);
	Wire.write(val);
	Wire.endTransmission();
}

uint8_t Gyroscope::readRegister(uint8_t reg){
	Wire.beginTransmission(L2GD20H_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();

	Wire.requestFrom(L2GD20H_ADDRESS,1);
	while(Wire.available()<1);
	uint8_t rtn = Wire.read();
	Wire.endTransmission();
	return rtn;
}

bool Gyroscope::isReady(){
	return ready;
}

//!!we need to handle errors here!
void Gyroscope::update(){
	Wire.beginTransmission(L2GD20H_ADDRESS);
	Wire.write(GYRO_REGISTER_OUT_X_L | 0x80);
	Wire.endTransmission();

	Wire.requestFrom(L2GD20H_ADDRESS,6);
	while(Wire.available() < 6);
	x = (Wire.read() | Wire.read() << 8) - xOffset;
	y = (Wire.read() | Wire.read() << 8) - yOffset;
	z = (Wire.read() | Wire.read() << 8) - zOffset;

	Wire.endTransmission();
}

void Gyroscope::calibrateOffset(){
	long xSum = 0;
	long ySum = 0;
	long zSum = 0;

	//first few samples are junk
	for(int i=0; i<CALIBRATION_JUNK; i++){
		update();
	}

	for(int i=0; i<CALIBRATION_SAMPLES;i++){
		update();
		xSum+=x;
		ySum+=y;
		zSum+=z;
	}

	xOffset = xSum/CALIBRATION_SAMPLES;
	yOffset = ySum/CALIBRATION_SAMPLES;
	zOffset = zSum/CALIBRATION_SAMPLES;
}