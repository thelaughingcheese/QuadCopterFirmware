#include "tests.h"
#include "ReceiverInput.h"

void gyroTest(){
	Gyroscope gyro;
	if(gyro.isReady()) gyro.calibrateOffset();

	for(;;){
		if(!gyro.isReady()) break;
		gyro.update();

		DEBUGSPRINT(gyro.convertAngularVelocity(gyro.x)) DEBUGSPRINT(", ")
		DEBUGSPRINT(gyro.convertAngularVelocity(gyro.y)) DEBUGSPRINT(", ")
		DEBUGSPRINTLN(gyro.convertAngularVelocity(gyro.z))

		delay(100);
	}
}

void accelTest(){
	Accelerometer accel;

	for(;;){
		accel.update();

		DEBUGSPRINT(accel.x) DEBUGSPRINT(", ")
		DEBUGSPRINT(accel.y) DEBUGSPRINT(", ")
		DEBUGSPRINTLN(accel.z)

		delay(100);
	}
}

void magTest(){
	Magnetometer mag;

	for(;;){
		mag.update();

		DEBUGSPRINT(mag.x) DEBUGSPRINT(", ")
		DEBUGSPRINT(mag.y) DEBUGSPRINT(", ")
		DEBUGSPRINTLN(mag.z)

		delay(100);
	}
}

void attTest(){
	AttitudeMeasurement att(AttitudeMeasurement::PITCH,AttitudeMeasurement::ROLL,AttitudeMeasurement::YAW);

	for(;;){
		att.update();

		DEBUGSPRINT(att.getAxisAngleAbsolute(att.PITCH)) DEBUGSPRINT(", ")
		DEBUGSPRINT(att.getAxisAngleAbsolute(att.ROLL)) DEBUGSPRINT(", ")
		DEBUGSPRINT(att.getAxisAngleAbsolute(att.YAW)) DEBUGSPRINT("\n")

		delay(100);
	}
}

void quadTest(){
	QuadCopter quadCopter(3,4,5,6,2000,700);
	for(;;){
		while(Serial.available() < 1);
		quadCopter.throttle = Serial.parseInt();
		quadCopter.update();
		DEBUGSPRINTLN(quadCopter.getRotorValue(0))
	}
}

void receiverTest(){
	for(;;){
		DEBUGSPRINT(channelCenterValue)DEBUGSPRINT(", ")
		DEBUGSPRINT(PITCH_CHANNEL)DEBUGSPRINT("\n")
		delay(100);
	}
}