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
		RATE_CONTROLLED = 0x02,
		RAW_CONTROLLED = 0x03
	} FlightMode;
private:
	QuadCopter* quadCopter;
	AttitudeMeasurement* attitudeMeasurement;
	FlightMode flightMode;

	PidController pitchControl;
	PidController rollControl;
	PidController yawControl;
public:
	FlightController(QuadCopter* copter, AttitudeMeasurement* att);
	void setMode(FlightMode mode);
	void begin();
};

#endif