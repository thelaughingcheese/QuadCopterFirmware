#include "PidController.h"

#define MICRO_TO_SEC_RATIO 0.000001

PidController::PidController(float p,float i,float d):
dFilter(15),
dFilter2(10){
	setGains(p,i,d);
	resetIComponent();
	setICap(0);

	reset = true;
	lastUpdate = micros();
}

void PidController::setGains(float p,float i,float d){
	pGain = p;
	iGain = i;
	dGain = d;
}

void PidController::setICap(float cap){
	iCap = cap;
}

float PidController::update(float input){
	float error = target - input;

	uint32_t deltaMicros;
	if(reset){
		deltaMicros = 1;
		reset = false;
	}
	else{
		deltaMicros = micros() - lastUpdate;
	}

	lastUpdate = micros();
	float deltaTime = MICRO_TO_SEC_RATIO * deltaMicros;
	float invDeltaTime = 1/deltaTime;

	errorIntegral += error*deltaTime*iGain;
	errorIntegral = max(-iCap,min(errorIntegral,iCap));

	float pComponent = error * pGain;
	float iComponent = errorIntegral;
	//float dComponent = dFilter2.update(error)*invDeltaTime*dGain;
	float dComponent = -dFilter2.update(input)*invDeltaTime*dGain;

	lastError = error;
	lastInput = input;

	lastPComponent = pComponent;
	lastIComponent = iComponent;
	lastDComponent = dComponent;

	return pComponent + iComponent + dComponent;
}

void PidController::resetIComponent(){
	errorIntegral = 0;
}