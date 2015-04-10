#include "QuadCopter.h"

QuadCopter::QuadCopter(int a,int b,int c,int d,int max,int min){
	rotorMax = max;
	rotorMin = min;

	rotors[0].setup(a,rotorMin,rotorMax);
	rotors[1].setup(b,rotorMin,rotorMax);
	rotors[2].setup(c,rotorMin,rotorMax);
	rotors[3].setup(d,rotorMin,rotorMax);
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