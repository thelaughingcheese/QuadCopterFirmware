#ifndef ESC
#define ESC

#include "Arduino.h"
#include <Servo.h>

class Esc{
private:
	Servo esc;
	long maxPulse;
	long minPulse;

public:
	long getMaxPulse(){ return maxPulse; }
	long getMinPulse(){ return minPulse; }

	Esc();
	Esc(int pin, long max, long min);
	void setup(int pin,short max,short min);
	void set(short val);
};

#endif