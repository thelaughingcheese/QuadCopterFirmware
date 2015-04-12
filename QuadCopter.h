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
#include "Gyroscope.h"
#include "Accelerometer.h"

class QuadCopter{
private:
	Esc rotors[4];
	long rotorMax;
	long rotorMin;
public:
	QuadCopter(int a, int b, int c, int d, int max, int min);
	void startUpNormal();
	void startSetConfigAndStart(EscConfiguration config);
};

#endif