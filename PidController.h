#ifndef PIDCONTROLLER
#define PIDCONTROLLER

#include "Arduino.h"

class PidController{
private:
	uint32_t lastUpdate;
	float errorIntegral;
	float lastError;
public:
	float pGain,iGain,dGain;
	float target;

	PidController(float p, float i, float d);
	float update(float input);
	void resetIComponent();
};

#endif