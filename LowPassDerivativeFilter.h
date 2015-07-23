#ifndef LOWPASSDERIVATIVEFILTER
#define LOWPASSDERIVATIVEFILTER

#define MAXDERIVATIVESAMPLES 100

class LowPassDerivativeFilter{
private:
	float samples[MAXDERIVATIVESAMPLES];
	int activeSamples;
	int sampleRange;
	int nextSampleIndex;

	int getNextIndex(int in);
	int getPrevIndex(int in);
	int getLastIndex();
public:
	LowPassDerivativeFilter(int range);

	float update(float in);
};

#endif