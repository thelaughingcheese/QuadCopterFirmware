#ifndef FLIGHTCONTROLLER
#define FLIGHTCONTROLLER

#include "Globals.h"
#include "AttitudeMeasurement.h"
#include "QuadCopter.h"
#include "PidController.h"
#include "ReceiverInput.h"

class FlightController{
public:
	typedef enum{
		ATTITUDE_CONTROLLED = 0x01,
		RATE_CONTROLLED = 0x02
	} FlightMode;
private:
	QuadCopter* quadCopter;
	AttitudeMeasurement* attitudeMeasurement;
	FlightMode flightMode;

	PidController pitchControl;
	PidController rollControl;
public:
	FlightController(QuadCopter* copter, AttitudeMeasurement* att);
	void setMode(FlightMode mode);
	void begin();
};

#endif