#include "LowPassDerivativeFilter.h"
#include <Arduino.h>

LowPassDerivativeFilter::LowPassDerivativeFilter(int range){
	sampleRange = range;
	activeSamples = 0;
	nextSampleIndex = 0;
}

int LowPassDerivativeFilter::getNextIndex(int in){
	return (in + 1)%sampleRange;
}

int LowPassDerivativeFilter::getPrevIndex(int in){
	return (in - 1 + sampleRange)%sampleRange;
}

int LowPassDerivativeFilter::getLastIndex(){
	return (nextSampleIndex - activeSamples + sampleRange)%sampleRange;
}

float LowPassDerivativeFilter::update(float in){
	samples[nextSampleIndex] = in;
	activeSamples = min(activeSamples+1,sampleRange);
	nextSampleIndex = getNextIndex(nextSampleIndex);

	float deltaY = in - samples[getLastIndex()];

	if(activeSamples == 1){
		return 0;
	}

	return deltaY/(activeSamples-1);
}