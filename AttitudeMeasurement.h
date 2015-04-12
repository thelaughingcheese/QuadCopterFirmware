#ifndef ATTITUDEMEASUREMENT
#define ATTITUDEMEASUREMENT

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"

typedef enum{
	PITCH = 1,
	ROLL = 2,
	YAW = 3
} Axis;

class AttitudeMeasurement{
private:
	Accelerometer accelerometer;
	Gyroscope gyroscope;
	Magnetometer magnetometer;
public:
	AttitudeMeasurement();

	//rate
	float getAxisAngleRate(Axis axis);

	//absolute
	float getAccelerometerAxisAngle(Axis axis);
	float getAxisAngleAbsolute(Axis axis);
};

#endif