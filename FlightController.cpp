#include "FlightController.h"

#define MAXANGLE 45

FlightController::FlightController(QuadCopter* copter,AttitudeMeasurement* att):
pitchControl(100,0,0),
rollControl(100,0,0),
yawControl(100,0,0){
	quadCopter = copter;
	attitudeMeasurement = att;
	setMode(RATE_CONTROLLED);
}

void FlightController::setMode(FlightMode mode){
	flightMode = mode;
}

void FlightController::begin(){
	for(;;){
		if(THROTTLE_CUT_CHANNEL < 0){
			quadCopter->throttle = 0;
			quadCopter->pitch = 0;
			quadCopter->roll = 0;
			quadCopter->yaw = 0;
			quadCopter->update();

			DEBUGSPRINTLN("Throttle cut!");

			continue;
		}

		if(flightMode == ATTITUDE_CONTROLLED){
			//read receiver, convert to angle
			long pitchAngle = (PITCH_CHANNEL*MAXANGLE)/CHMAXVAL;
			long rollAngle = (ROLL_CHANNEL*MAXANGLE)/CHMAXVAL;
			long yawRate = (YAW_CHANNEL*90)/CHMAXVAL;

			//set pid target angle
			pitchControl.target = pitchAngle;
			rollControl.target = rollAngle;
			yawControl.target = yawRate;

			//update pid
			attitudeMeasurement->update();
			long throttleOut = (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2);
			long pitchOut = pitchControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::PITCH));
			long rollOut = rollControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL));
			long yawOut = yawControl.update(-attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::YAW));			//flipped!!!

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();

			/*
				DEBUGSPRINT(quadCopter->throttle); DEBUGSPRINT(", ");
				DEBUGSPRINT(quadCopter->pitch); DEBUGSPRINT(", ");
				DEBUGSPRINT(quadCopter->roll); DEBUGSPRINT(", ");
				DEBUGSPRINT(quadCopter->yaw); DEBUGSPRINT("\n");
			*/	

				/*
				DEBUGSPRINT(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::PITCH)); DEBUGSPRINT(", ");
				DEBUGSPRINT(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL)); DEBUGSPRINT(", ");
				DEBUGSPRINT(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::YAW)); DEBUGSPRINT("\n");
				*/

				analogWrite(A14,(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL))*255/90);
		}
		else if(flightMode == RATE_CONTROLLED){
			//read receiver
			//read receiver, convert to angle
			long pitchRate = (PITCH_CHANNEL*90)/CHMAXVAL;
			long rollRate = (ROLL_CHANNEL*90)/CHMAXVAL;
			long yawRate = (YAW_CHANNEL*90)/CHMAXVAL;

			//set pid target angle
			pitchControl.target = pitchRate;
			rollControl.target = rollRate;
			yawControl.target = yawRate;

			//update pid
			attitudeMeasurement->update();
			long throttleOut = (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2);
			long pitchOut = pitchControl.update(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::PITCH));
			long rollOut = rollControl.update(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::ROLL));
			long yawOut = yawControl.update(-attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::YAW));			//flipped!!!

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();
		}
		else if(flightMode == RAW_CONTROLLED){
			//read receiver
			long pitchOut = (PITCH_CHANNEL*INT_SHORT_MAX)/CHMAXVAL;
			long rollOut = (ROLL_CHANNEL*INT_SHORT_MAX)/CHMAXVAL;
			long yawOut = (YAW_CHANNEL*INT_SHORT_MAX)/CHMAXVAL;
			long throttleOut = (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2);

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();
		}
		else{
			DEBUGSPRINTLN("invalid Flight Mode");
			break;
		}

		delay(1);	//remove this and see what happens

		//benchmarking
		pinMode(0,OUTPUT);
		digitalWriteFast(0,HIGH);
		delayMicroseconds(50);
		digitalWriteFast(0,LOW);
	}
}