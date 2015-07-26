#include "FlightController.h"
#include "DataLogger.h"

#define MAXANGLE 45

FlightController::FlightController(QuadCopter* copter,AttitudeMeasurement* att):
pitchAttitudeControl(0,0,0),
rollAttitudeControl(0,0,0),
yawAttitudeControl(0,0,0),
pitchVelocityControl(0,0,0),
rollVelocityControl(0,0,0),
yawVelocityControl(0,0,0){
	quadCopter = copter;
	attitudeMeasurement = att;
	setMode(ATTITUDE_CONTROLLED);

	pitchVelocityControl.setICap(8000);
	rollVelocityControl.setICap(8000);
	yawVelocityControl.setICap(8000);

	pitchAttitudeControl.setICap(180);
	rollAttitudeControl.setICap(180);
	yawAttitudeControl.setICap(180);
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

			pitchAttitudeControl.resetIComponent();
			rollAttitudeControl.resetIComponent();
			yawAttitudeControl.resetIComponent();

			pitchVelocityControl.resetIComponent();
			rollVelocityControl.resetIComponent();
			yawVelocityControl.resetIComponent();

			attitudeMeasurement->resetMeasurement();

			DEBUGSPRINTLN("Throttle cut!");

			continue;
		}
		#pragma endregion

		#pragma region attitude control mode
		if(flightMode == ATTITUDE_CONTROLLED){
			pitchAttitudeControl.setGains(0.7,0.8,0.1);
			rollAttitudeControl.setGains(0.7,0.8,0.1);

			pitchVelocityControl.setGains(15,120,0);
			rollVelocityControl.setGains(15,120,0);
			yawVelocityControl.setGains(100,10,0);

			//read receiver, convert to angle
			long pitchAngle = (PITCH_CHANNEL*MAXANGLE)/CHMAXVAL;
			long rollAngle = (ROLL_CHANNEL*MAXANGLE)/CHMAXVAL;
			long yawRate = (YAW_CHANNEL*90)/CHMAXVAL;

			//set attitude pid target angle
			pitchAttitudeControl.target = pitchAngle;
			rollAttitudeControl.target = rollAngle;

			//update attitude pid
			attitudeMeasurement->update();
			long pitchRate = pitchAttitudeControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::PITCH));
			long rollRate = rollAttitudeControl.update(attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL));

			//set velocity pid target angle
			pitchVelocityControl.target = pitchRate;
			rollVelocityControl.target = rollRate;
			yawVelocityControl.target = yawRate;

			//update velocity pid
			long throttleOut = (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2);
			long pitchOut = pitchVelocityControl.update(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::PITCH));
			long rollOut = rollVelocityControl.update(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::ROLL));
			long yawOut = yawVelocityControl.update(-attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::YAW));

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();

			//logging
			tbuff[buffIndex] = rollAngle;
			pbuff[buffIndex] = attitudeMeasurement->getAxisAngleAbsolute(AttitudeMeasurement::ROLL);
			ibuff[buffIndex] = rollAttitudeControl.lastIComponent;

			buffIndex++;

			if(buffIndex == 4000){
				quadCopter->throttle = 0;quadCopter->pitch = 0;	quadCopter->roll = 0;quadCopter->yaw = 0;
				quadCopter->update();

				LogData();

				for(;;){
					quadCopter->throttle = 0;quadCopter->pitch = 0;	quadCopter->roll = 0;quadCopter->yaw = 0;
					quadCopter->update();
				}
			}
		}
		#pragma endregion

		#pragma region rate control mode
		else if(flightMode == RATE_CONTROLLED){
			pitchVelocityControl.setGains(15,120,0);
			rollVelocityControl.setGains(15,120,0);
			yawVelocityControl.setGains(100,10,0);

			//read receiver, convert to angle
			long pitchRate = (PITCH_CHANNEL*90)/CHMAXVAL;
			long rollRate = (ROLL_CHANNEL*90)/CHMAXVAL;
			long yawRate = (YAW_CHANNEL*90)/CHMAXVAL;

			//set pid target angular velocity
			pitchVelocityControl.target = pitchRate;
			rollVelocityControl.target = rollRate;
			yawVelocityControl.target = yawRate;

			//update pid
			attitudeMeasurement->update();
			long throttleOut = (THROTTLE_CHANNEL*INT_SHORT_MAX)/(CHMAXVAL*2);
			long pitchOut = pitchVelocityControl.update(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::PITCH));
			long rollOut = rollVelocityControl.update(attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::ROLL));
			long yawOut = yawVelocityControl.update(-attitudeMeasurement->getAxisAngleRate(AttitudeMeasurement::YAW));			//flipped!!!

			//update quadcopter
			quadCopter->throttle = min(max(throttleOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->pitch = min(max(pitchOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->roll = min(max(rollOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->yaw = min(max(yawOut,INT_SHORT_MIN),INT_SHORT_MAX);
			quadCopter->update();

			//logging
			/*tbuff[buffIndex] = rollRate;
			pbuff[buffIndex] = rollVelocityControl.lastPComponent;
			ibuff[buffIndex] = rollVelocityControl.lastIComponent;

			buffIndex++;

			if(buffIndex == 4000){
				quadCopter->throttle = 0;quadCopter->pitch = 0;	quadCopter->roll = 0;quadCopter->yaw = 0;
				quadCopter->update();

				LogData();

				for(;;){
					quadCopter->throttle = 0;quadCopter->pitch = 0;	quadCopter->roll = 0;quadCopter->yaw = 0;
					quadCopter->update();
				}
			}*/
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