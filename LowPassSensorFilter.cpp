#include "LowPassSensorFilter.h"
#include "Arduino.h"

int LowPassSensorFilter::getNextIndex(int in){
	int rtn = in + 1;
	if(rtn >= MAXSAMPLES){
		return 0;
	}
	return rtn;
}

int LowPassSensorFilter::getPrevIndex(int in){
	int rtn = in - 1;
	if(rtn < 0){
		return MAXSAMPLES-1;
	}
	return rtn;
}

LowPassSensorFilter::LowPassSensorFilter(short range){
	activeSamples = 0;
	sampleRange = range;
	nextSampleIndex = 0;
}

short LowPassSensorFilter::update(short in){
	samples[nextSampleIndex] = in;
	activeSamples = min(activeSamples+1,sampleRange);
	long total = 0;

	int index = nextSampleIndex;
	for(int i=0;i<activeSamples;i++){
		total += samples[index];
		index = getPrevIndex(index);
	}

	nextSampleIndex = getNextIndex(nextSampleIndex);
	return total/sampleRange;
}