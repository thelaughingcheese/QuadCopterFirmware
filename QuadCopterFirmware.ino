#include <Servo.h>
#include <Wire.h>
#include "Globals.h"
#include "ReceiverInput.h"
#include "QuadCopter.h"
#include "AttitudeMeasurement.h"

#include "tests.h"

QuadCopter quadCopter(3,4,5,6,2000,700);

void setup()
{
	DEBUGSBEGIN
	DEBUGSPRINTLN("start")

	void setupReceiverInput();
	//quadCopter.startUpNormal();
	Wire.begin();

	DEBUGSPRINTLN("setup end")
}

void loop()
{


	DEBUGSPRINTLN("shutting down!")
	for(pinMode(13,OUTPUT);;){ 
		digitalWriteFast(13,HIGH);
		delay(100);
		digitalWriteFast(13,LOW);
		delay(100);
	}
}
