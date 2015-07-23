#include "ServoModified.h"
#include "Globals.h"
//#include <Wire.h>
#include "ReceiverInput.h"
#include "QuadCopter.h"
#include "AttitudeMeasurement.h"
#include "FlightController.h"
#include <SPI.h>
#include <SD.h>
#include "DataLogger.h"

#include "tests.h"

void setup()
{
	pinMode(13,OUTPUT);
	pinMode(1,OUTPUT);

	DEBUGSBEGIN;
	//delay(200);	//allow i2c devices to initialize

	DEBUGSPRINTLN("start");

	pinMode(2,INPUT);
	while(!digitalReadFast(2));

	setupReceiverInput();
	//calibrateChannelCenterValue();

	DEBUGSPRINTLN("setup end");
}

void loop()
{
	EscConfiguration config;

	QuadCopter quadCopter(3,4,5,6,2000,700);
	quadCopter.startUpNormal();
	//quadCopter.startSetConfigAndStart(config);
quadinst=&quadCopter;

	AttitudeMeasurement attitudeMeasurement(AttitudeMeasurement::PITCH,AttitudeMeasurement::ROLL,AttitudeMeasurement::YAW);
	DEBUGSPRINTLN("GO!");
	digitalWriteFast(13,HIGH);

	FlightController controller(&quadCopter,&attitudeMeasurement);
	controller.begin();

	//quadTest();
	//receiverTest();

	DEBUGSPRINTLN("shutting down!")
	for(;;){ 
		digitalWriteFast(13,HIGH);
		delay(100);
		digitalWriteFast(13,LOW);
		delay(100);
	}
}
