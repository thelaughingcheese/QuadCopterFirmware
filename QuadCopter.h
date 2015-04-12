/*
top down view
---    ---
|a|    |b|
---    ---
   \  /
    \/
	/\
   /  \
---    ---
|c|    |d|
---    ---


increasing pitch raises a and b
increasing roll raises a and c
increasing yaw rotates clockwise
*/

#ifndef QUADCOPTER
#define QUADCOPTER

#include "EscStartupManager.h"
#include "AttitudeMeasurement.h"

class QuadCopter{
private:
	AttitudeMeasurement attitudeMeasurement;

	Esc rotors[4];
	long rotorMax;
	long rotorMin;
public:
	QuadCopter(int a, int b, int c, int d, int max, int min);
	void startUpNormal();
	void startSetConfigAndStart(EscConfiguration config);
};

#endif