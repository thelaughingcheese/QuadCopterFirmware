#include "PidController.h"

#define MICRO_TO_SEC_RATIO 0.000001

PidController::PidController(float p,float i,float d):
dFilter(15){
	setGains(p,i,d);
	resetIComponent();

	lastUpdate = micros();
}

void PidController::setGains(float p,float i,float d){
	pGain = p;
	iGain = i;
	dGain = d;
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
	float dComponent = dFilter.update(error - lastError)*invDeltaTime*dGain;

	lastError = error;

	return pComponent + iComponent + dComponent;
}

void PidController::resetIComponent(){
	errorIntegral = 0;
}