#include "QuadCopter.h"

QuadCopter::QuadCopter(int a,int b,int c,int d,int max,int min){
	//rotor setup
	rotorMax = max;
	rotorMin = min;
	rotorRange = max-min;

	rotors[0].setup(a,rotorMin,rotorMax);
	rotors[1].setup(b,rotorMin,rotorMax);
	rotors[2].setup(c,rotorMin,rotorMax);
	rotors[3].setup(d,rotorMin,rotorMax);

	pitch = 0; roll = 0; yaw = 0; throttle = 0;
}

//blocks until finished!
void QuadCopter::startUpNormal(){
	EscStartupManager startupManager(rotors,4);

	startupManager.startupAllNormal();
}

void QuadCopter::startSetConfigAndStart(EscConfiguration config){
	EscStartupManager startupManager(rotors,4);

	startupManager.setConfigurationAll(config);
	startupManager.applyConfigurationAll();
}

//need to floor values
void QuadCopter::update(){
	short pitchScaled = (pitch*rotorRange/INT_SHORT_MAX);
	short rollScaled = (roll*rotorRange/INT_SHORT_MAX);
	short yawScaled = (yaw*rotorRange/INT_SHORT_MAX);
	short throttleScaled = (throttle*rotorRange/INT_SHORT_MAX);

	//throttle
	short a = rotorMin + throttleScaled;
	short b = rotorMin + throttleScaled;
	short c = rotorMin + throttleScaled;
	short d = rotorMin + throttleScaled;

	//pitch
	a += pitchScaled;
	b += pitchScaled;
	c -= pitchScaled;
	d -= pitchScaled;

	//roll
	a += rollScaled;
	b -= rollScaled;
	c += rollScaled;
	d -= rollScaled;

	//yaw
	a -= yawScaled;
	b += yawScaled;
	c += yawScaled;
	d -= yawScaled;

	rotors[0].set(a);
	rotors[1].set(b);
	rotors[2].set(c);
	rotors[3].set(d);
}

int QuadCopter::getRotorValue(int rotor){
	return rotors[rotor].get();
}