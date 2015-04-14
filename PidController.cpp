#include "PidController.h"

#define MICRO_TO_SEC_RATIO 0.000001

PidController::PidController(float p,float i,float d){
	pGain = p;
	iGain = i;
	dGain = d;

	lastUpdate = micros();
}

float PidController::update(float input){
	float error = target - input;

	uint32_t deltaMicros = micros() - lastUpdate;
	lastUpdate = micros();
	float deltaTime = MICRO_TO_SEC_RATIO * deltaMicros;
	float invDeltaTime = 1/deltaTime;

	errorIntegral += error*deltaTime*iGain;

	float pComponent = error * pGain;
	float iComponent = errorIntegral;
	float dComponent = (error - lastError)*invDeltaTime*dGain;

	lastError = error;

	return pComponent + iComponent + dComponent;
}