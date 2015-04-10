#include "Esc.h"

Esc::Esc(){
}

Esc::Esc(int pin,long max,long min){
	setup(pin,max,min);
}

void Esc::setup(int pin,long max,long min){
	esc.attach(pin);
	maxPulse = max;
	minPulse = min;
}

void Esc::set(int width){
	esc.writeMicroseconds(width);
}