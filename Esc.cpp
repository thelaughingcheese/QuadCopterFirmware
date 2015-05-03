#include "Esc.h"

Esc::Esc(){
}

Esc::Esc(int pin,long max,long min){
	setup(pin,max,min);
	set(min);
}

void Esc::setup(int pin,short max,short min){
	esc.attach(pin);
	maxPulse = max;
	minPulse = min;
}