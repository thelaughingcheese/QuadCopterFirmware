#include "Gyroscope.h"

float Gyroscope::convertAngularVelocity(int16_t angularVelocity){
	int wordSignedMaxValue = 0x7fff;

	float maxVelocity;

	if(maxAngularVelocity == DPS245){
		maxVelocity = 245;
	}
	else if(maxAngularVelocity == DPS500){
		maxVelocity = 500;
	}
	else{
		maxVelocity = 2000;
	}

	return (maxVelocity*angularVelocity) / wordSignedMaxValue;
}

//configure
Gyroscope::Gyroscope(): I2cDevice(L2GD20H_ADDRESS){
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

	//set config reg 4, default 245 dps
	maxAngularVelocity = DPS245;
	writeRegister(GYRO_REGISTER_CTRL_REG4,maxAngularVelocity);

	x=0;y=0;z=0;
	xOffset=0;yOffset=0;zOffset=0;

	ready = true;
}

void Gyroscope::setMaxAngularVelocity(Gyroscope::MaxAngularVelocity max){
	maxAngularVelocity = max;
	writeRegister(GYRO_REGISTER_CTRL_REG4,max);
}

//!!we need to handle errors here!
void Gyroscope::update(){
	for(;;){
analogWriteDAC0(0);
		Wire.beginTransmission(deviceAddress);
analogWriteDAC0(607);
		Wire.write(GYRO_REGISTER_OUT_X_L | 0x80);
analogWriteDAC0(1214);
		if(Wire.endTransmission()){	//200us
			Wire.begin();
			continue;
		}
analogWriteDAC0(1821);

		if(Wire.requestFrom(deviceAddress,6) == 0){	//700us
			Wire.begin();
			continue;
		}
analogWriteDAC0(2430);
		while(Wire.available() < 6){ analogWriteDAC0(0); };
analogWriteDAC0(3036);
		x = (Wire.read() | Wire.read() << 8) - xOffset;
		y = (Wire.read() | Wire.read() << 8) - yOffset;		//all this 2us
		z = (Wire.read() | Wire.read() << 8) - zOffset;
analogWriteDAC0(3643);
	if(Wire.endTransmission()){	//200us
		Wire.begin();
		continue;
	}
analogWriteDAC0(4000);
		break;
	}
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