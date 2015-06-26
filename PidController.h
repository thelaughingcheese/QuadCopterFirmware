#ifndef PIDCONTROLLER
#define PIDCONTROLLER

#include "Arduino.h"
#include "LowPassSensorFilter.h"

class PidController{
private:
	uint32_t lastUpdate;
	float errorIntegral;
	float lastError;
	float lastInput;
	float iCap;

	LowPassSensorFilter<float> dFilter;
public:
	float pGain,iGain,dGain;
	float target;

	PidController(float p, float i, float d);
	void setGains(float p,float i,float d);
	void setICap(float cap);
	float update(float input);
	void resetIComponent();
};

#endif