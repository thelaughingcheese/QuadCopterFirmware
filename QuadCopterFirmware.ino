#include <Servo.h>
#include <Wire.h>
#include "Globals.h"
#include "ReceiverInput.h"
#include "QuadCopter.h"
#include "AttitudeMeasurement.h"
#include "FlightController.h"

#include "tests.h"

QuadCopter quadCopter(3,4,5,6,2000,700);
AttitudeMeasurement attitudeMeasurement(AttitudeMeasurement::PITCH,AttitudeMeasurement::ROLL,AttitudeMeasurement::YAW);

void setup()
{
	DEBUGSBEGIN
	DEBUGSPRINTLN("start")

	quadCopter.startUpNormal();

	setupReceiverInput();
	//calibrateChannelCenterValue();

	DEBUGSPRINTLN("setup end")
}

void loop()
{
	//FlightController controller(&quadCopter,&attitudeMeasurement);
	//controller.begin();

	//quadTest();
	receiverTest();

	DEBUGSPRINTLN("shutting down!")
	for(pinMode(13,OUTPUT);;){ 
		digitalWriteFast(13,HIGH);
		delay(100);
		digitalWriteFast(13,LOW);
		delay(100);
	}
}
