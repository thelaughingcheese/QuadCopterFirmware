#include "FlightController.h"

#define MAXANGLE 45

FlightController::FlightController(QuadCopter* copter,AttitudeMeasurement* att):
pitchControl(0,0,0),
rollControl(0,0,0){
	quadCopter = copter;
	attitudeMeasurement = att;
	setMode(ATTITUDE_CONTROLLED);
}

void FlightController::setMode(FlightMode mode){
	flightMode = mode;
}

void FlightController::begin(){
	for(;;){
		if(flightMode == ATTITUDE_CONTROLLED){
			//read receiver, convert to angle
			long pitchAngle = (PITCH_CHANNEL*MAXANGLE)/CHMAXVAL;
			long rollAngle = (ROLL_CHANNEL*MAXANGLE)/CHMAXVAL;

			//set pid target angle
			pitchControl.target = pitchAngle;
			rollControl.target = rollAngle;

			//update pid
			attitudeMeasurement->update();
			long pitchOut = pitchControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::PITCH));
			long rollOut = rollControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL));

			//update quadcopter
			quadCopter->pitch = pitchOut;
			quadCopter->roll = rollOut;
			quadCopter->update();
		}
		else if(flightMode == RATE_CONTROLLED){
			//read receiver
			DEBUGSPRINTLN("rate Flight Mode not implemented");
			break;

		}
		else{
			DEBUGSPRINTLN("invalid Flight Mode");
			break;
		}
	}
}