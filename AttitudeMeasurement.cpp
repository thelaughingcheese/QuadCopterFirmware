#include "AttitudeMeasurement.h"

#define RAD_TO_DEG_RATIO 57.295779513082320876798154814105
#define MICRO_TO_SEC_RATIO 0.000001

AttitudeMeasurement::AttitudeMeasurement(Axis X,Axis Y,Axis Z):
gyroXFilter(10),
gyroYFilter(10),
gyroZFilter(10),
accelXFilter(20),
accelYFilter(20),
accelZFilter(20){
	xMapping = X;
	yMapping = Y;
	zMapping = Z;

	pitch = 0;
	roll = 0;
	yaw = 0;

	gyroscope.calibrateOffset();

	lastUpdate = micros();
}

float AttitudeMeasurement::getAxisAngleRate(Axis axis){
	if(xMapping == axis) return gyroscope.convertAngularVelocity(gyroX);
	else if(yMapping == axis) return gyroscope.convertAngularVelocity(gyroY);
	else if(zMapping == axis) return gyroscope.convertAngularVelocity(gyroZ);
}

float AttitudeMeasurement::getAccelerometerAxisAngle(Axis axis){
	if(xMapping == axis){
		float rtn;

		if(accelZ == 0){
			rtn = RAD_TO_DEG_RATIO*atan((float)accelY);
		}
		else{
			if(accelZ < 0 && accelY > 0){
				rtn = 180 + RAD_TO_DEG_RATIO*atan((float)accelY/accelZ);
			}
			else if(accelZ < 0 && accelY < 0){
				rtn = -180 + RAD_TO_DEG_RATIO*atan((float)accelY/accelZ);
			}
			else{
				rtn = RAD_TO_DEG_RATIO*atan((float)accelY/accelZ);
			}
		}
		return rtn;
	}
	else if(yMapping == axis){
		float rtn;

		if(accelZ == 0){
			rtn = RAD_TO_DEG_RATIO*atan((float)accelX);
		}
		else{
			if(accelZ < 0 && accelX > 0){
				rtn = 180 + RAD_TO_DEG_RATIO*atan((float)accelX/accelZ);
			}
			else if(accelZ < 0 && accelX < 0){
				rtn = -180 + RAD_TO_DEG_RATIO*atan((float)accelX/accelZ);
			}
			else{
				rtn = RAD_TO_DEG_RATIO*atan((float)accelX/accelZ);
			}
		}
		return -rtn;
	}
	else if(zMapping == axis){
		float rtn;

		if(accelY == 0){
			rtn = RAD_TO_DEG_RATIO*atan((float)accelX);
		}
		else{
			if(accelY < 0 && accelX > 0){
				rtn = 180 + RAD_TO_DEG_RATIO*atan((float)accelX/accelY);
			}
			else if(accelY < 0 && accelX < 0){
				rtn = -180 + RAD_TO_DEG_RATIO*atan((float)accelX/accelY);
			}
			else{
				rtn = RAD_TO_DEG_RATIO*atan((float)accelX/accelY);
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

	//filter
	gyroX = gyroXFilter.update(gyroscope.x);
	gyroY = gyroYFilter.update(gyroscope.y);
	gyroZ = gyroZFilter.update(gyroscope.z);

	accelX = accelXFilter.update(accelerometer.x);
	accelY = accelYFilter.update(accelerometer.y);
	accelZ = accelZFilter.update(accelerometer.z);

	//calc absolute stuffs
	uint32_t deltaMicroSeconds = micros() - lastUpdate;
	lastUpdate = micros();
	float deltaTime = MICRO_TO_SEC_RATIO*deltaMicroSeconds;

	float predictedPitch = pitch + getAxisAngleRate(PITCH)*deltaTime;
	float predictedRoll = roll + getAxisAngleRate(ROLL)*deltaTime;
	float predictedYaw = yaw + getAxisAngleRate(YAW)*deltaTime;

	pitch = 0.98*predictedPitch + 0.02*getAccelerometerAxisAngle(PITCH);
	roll = 0.98*predictedRoll + 0.02*getAccelerometerAxisAngle(ROLL);
	yaw = 0.98*predictedYaw + 0.02*getAccelerometerAxisAngle(YAW);

	//debug!! vibration analysis
	analogWriteDAC0((getAccelerometerAxisAngle(PITCH)+INT_SHORT_MAX)*4069/(INT_SHORT_MAX*2));
}