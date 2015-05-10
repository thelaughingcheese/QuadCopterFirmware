#ifndef LOWPASSSENSORFILTER
#define LOWPASSSENSORFILTER

#define MAXSAMPLES 100

class LowPassSensorFilter{
private:
	short samples[MAXSAMPLES];
	short activeSamples;
	short sampleRange;
	int nextSampleIndex;

	int getNextIndex(int in);
	int getPrevIndex(int in);
public:
	LowPassSensorFilter(short range);

	short update(short in);
};

#endif