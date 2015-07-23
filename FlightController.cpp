#include "FlightController.h"

#define MAXANGLE 45

FlightController::FlightController(QuadCopter* copter,AttitudeMeasurement* att):
pitchControl(0,0,0),
rollControl(0,0,0),
yawControl(0,0,0){
	quadCopter = copter;
	attitudeMeasurement = att;
	setMode(ATTITUDE_CONTROLLED);

	pitchControl.setICap(8000);
	rollControl.setICap(8000);
	yawControl.setICap(8000);
}

void FlightController::setMode(FlightMode mode){
	flightMode = mode;
}

void FlightController::begin(){
	#pragma region safety block until throttle cut and set to 0
	while(THROTTLE_CUT_CHANNEL > 0 || (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2) > 0){
		digitalWriteFast(13,HIGH);
		delay(500);
		digitalWriteFast(13,LOW);
		delay(500);

		DEBUGSPRINTLN("Throttledown to start!");
	}
	digitalWriteFast(13,LOW);
	#pragma endregion

	for(;;){
		#pragma region safety throttle cut
		if(THROTTLE_CUT_CHANNEL < 0){
			quadCopter->throttle = 0;
			quadCopter->pitch = 0;
			quadCopter->roll = 0;
			quadCopter->yaw = 0;
			quadCopter->update();

			pitchControl.resetIComponent();
			rollControl.resetIComponent();
			yawControl.resetIComponent();

			DEBUGSPRINTLN("Throttle cut!");

			continue;
		}
		#pragma endregion

		#pragma region attitude control mode
		if(flightMode == ATTITUDE_CONTROLLED){
			pitchControl.setGains(120,180,25);
			rollControl.setGains(130,20,12.5);
			yawControl.setGains(40,0,0);

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
			long pitchOut = pitchControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::PITCH));0;
			long rollOut = rollControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL));
			long yawOut = yawControl.update(-attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::YAW));0;			//flipped!!!

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();
		}
		#pragma endregion

		#pragma region rate control mode
		else if(flightMode == RATE_CONTROLLED){
			pitchControl.setGains(100,0,0);
			rollControl.setGains(100,0,0);
			yawControl.setGains(100,0,0);

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

			
			DEBUGSPRINT(quadCopter->throttle); DEBUGSPRINT(", ");
			DEBUGSPRINT(quadCopter->pitch); DEBUGSPRINT(", ");
			DEBUGSPRINT(quadCopter->roll); DEBUGSPRINT(", ");
			DEBUGSPRINT(quadCopter->yaw); DEBUGSPRINT("\n");
			
		}
		#pragma endregion

		#pragma region raw control mode
		else if(flightMode == RAW_CONTROLLED){
			//read receiver
			long pitchOut = (PITCH_CHANNEL*INT_SHORT_MAX)/CHMAXVAL;
			long rollOut = (ROLL_CHANNEL*INT_SHORT_MAX)/CHMAXVAL;
			long yawOut = (YAW_CHANNEL*INT_SHORT_MAX)/CHMAXVAL;
			long throttleOut = (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2);

			attitudeMeasurement->update();

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();
		}
		#pragma endregion

		#pragma region invalid control mode
		else{
			DEBUGSPRINTLN("invalid Flight Mode");
			break;
		}
		#pragma endregion

		//delay(1);	//remove this and see what happens

		#pragma region benchmarking
		pinMode(0,OUTPUT);
		digitalWriteFast(0,HIGH);
		delayMicroseconds(50);
		digitalWriteFast(0,LOW);
		#pragma endregion
	}
}