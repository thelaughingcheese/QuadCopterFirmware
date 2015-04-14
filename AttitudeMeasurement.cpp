#include "AttitudeMeasurement.h"

#define RAD_TO_DEG_RATIO 57.295779513082320876798154814105
#define MICRO_TO_SEC_RATIO 0.000001

AttitudeMeasurement::AttitudeMeasurement(Axis X,Axis Y,Axis Z){
	xMapping = X;
	yMapping = Y;
	zMapping = Z;

	pitch = 0;
	roll = 0;
	yaw = 0;

	lastUpdate = micros();
}

float AttitudeMeasurement::getAxisAngleRate(Axis axis){
	if(xMapping == axis) return gyroscope.convertAngularVelocity(gyroscope.x);
	else if(yMapping == axis) return gyroscope.convertAngularVelocity(gyroscope.y);
	else if(zMapping == axis) return gyroscope.convertAngularVelocity(gyroscope.z);
}

float AttitudeMeasurement::getAccelerometerAxisAngle(Axis axis){
	if(xMapping == axis){
		float rtn;

		if(accelerometer.z == 0){
			rtn = RAD_TO_DEG_RATIO*atan((float)accelerometer.y);
		}
		else{
			if(accelerometer.z < 0 && accelerometer.y > 0){
				rtn = 180 + RAD_TO_DEG_RATIO*atan((float)accelerometer.y/accelerometer.z);
			}
			else if(accelerometer.z < 0 && accelerometer.y < 0){
				rtn = -180 + RAD_TO_DEG_RATIO*atan((float)accelerometer.y/accelerometer.z);
			}
			else{
				rtn = RAD_TO_DEG_RATIO*atan((float)accelerometer.y/accelerometer.z);
			}
		}
		return rtn;
	}
	else if(yMapping == axis){
		float rtn;

		if(accelerometer.z == 0){
			rtn = RAD_TO_DEG_RATIO*atan((float)accelerometer.x);
		}
		else{
			if(accelerometer.z < 0 && accelerometer.x > 0){
				rtn = 180 + RAD_TO_DEG_RATIO*atan((float)accelerometer.x/accelerometer.z);
			}
			else if(accelerometer.z < 0 && accelerometer.x < 0){
				rtn = -180 + RAD_TO_DEG_RATIO*atan((float)accelerometer.x/accelerometer.z);
			}
			else{
				rtn = RAD_TO_DEG_RATIO*atan((float)accelerometer.x/accelerometer.z);
			}
		}
		return -rtn;
	}
	else if(zMapping == axis){
		float rtn;

		if(accelerometer.y == 0){
			rtn = RAD_TO_DEG_RATIO*atan((float)accelerometer.x);
		}
		else{
			if(accelerometer.y < 0 && accelerometer.x > 0){
				rtn = 180 + RAD_TO_DEG_RATIO*atan((float)accelerometer.x/accelerometer.y);
			}
			else if(accelerometer.y < 0 && accelerometer.x < 0){
				rtn = -180 + RAD_TO_DEG_RATIO*atan((float)accelerometer.x/accelerometer.y);
			}
			else{
				rtn = RAD_TO_DEG_RATIO*atan((float)accelerometer.x/accelerometer.y);
			}
		}
		return rtn;
	}
}

float AttitudeMeasurement::getAxisAngleAbsolute(Axis axis){
	if(axis == PITCH) return pitch;
	else if(axis == ROLL) return roll;
	else if(axis == YAW) return yaw;
}

//does not encorporate magnetometer, uses complementary filter
void AttitudeMeasurement::update(){
	gyroscope.update();
	accelerometer.update();
	magnetometer.update();

	//calc absolute stuffs
	uint32_t deltaMicroSeconds = micros() - lastUpdate;
	lastUpdate = micros();
	float deltaTime = MICRO_TO_SEC_RATIO*deltaMicroSeconds;

	float predictedPitch = pitch + getAxisAngleRate(PITCH)*deltaTime;
	float predictedRoll = roll + getAxisAngleRate(ROLL)*deltaTime;
	float predictedYaw = yaw + getAxisAngleRate(YAW)*deltaTime;

	pitch = 0.98*getAccelerometerAxisAngle(PITCH) + 0.02*predictedPitch;
	roll = 0.98*getAccelerometerAxisAngle(ROLL) + 0.02*predictedRoll;
	yaw = 0.98*getAccelerometerAxisAngle(YAW) + 0.02*predictedYaw;
}