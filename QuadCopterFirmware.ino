#include <Servo.h>
#include <Wire.h>
#include "Globals.h"
#include "ReceiverInput.h"
#include "QuadCopter.h"

QuadCopter quadCopter(3,4,5,6,2000,700);

void setup()
{
	DEBUGSBEGIN
	DEBUGSPRINTLN("start")

	void setupReceiverInput();
	quadCopter.startUpNormal();
	Wire.begin();
}

void loop()
{
	Gyroscope gyro;
	if(gyro.isReady()) gyro.calibrateOffset();
	
	for(;;){
		if(!gyro.isReady()) break;
		gyro.update();
		DEBUGSPRINT(gyro.x) DEBUGSPRINT(", ")
		DEBUGSPRINT(gyro.y) DEBUGSPRINT(", ")
		DEBUGSPRINTLN(gyro.z)
		delay(100);
	}

	DEBUGSPRINTLN("shutting down!")
	for(pinMode(13,OUTPUT);;){ 
		digitalWriteFast(13,HIGH);
		delay(100);
		digitalWriteFast(13,LOW);
		delay(100);
	}
}
