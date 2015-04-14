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
	assuming b and c are rotating anti-clockwise
*/

#ifndef QUADCOPTER
#define QUADCOPTER

#include "Globals.h"
#include "EscStartupManager.h"

class QuadCopter{
public:
private:
	//AttitudeMeasurement attitudeMeasurement;

	Esc rotors[4];
	short rotorMax;
	short rotorMin;
	short rotorRange;
public:
	short pitch,roll,yaw,throttle;

	QuadCopter(int a, int b, int c, int d, int max, int min);
	void startUpNormal();
	void startSetConfigAndStart(EscConfiguration config);

	void update();
};

#endif