#ifndef ESCCONFIGURATION
#define ESCCONFIGURATION

class EscConfiguration{
private:
public:
	typedef enum{
		BRAKE_ON,
		BRAKE_OFF
	} Brake;
	typedef enum{
		LIPO,
		NICD
	} BatteryType;
	typedef enum{
		SOFT_CUTOFF,
		HARD_CUTOFF
	} CutoffMode;
	typedef enum{
		LOW_THRESHOLD,
		MEDIUM_THRESHOLD,
		HIGH_THRESHOLD
	} CutoffThreshold;
	typedef enum{
		NORMAL_START,
		SOFT_START,
		SUPERSOFT_START
	} StartMode;
	typedef enum{
		LOW_TIMING,
		MEDIUM_TIMING,
		HIGH_TIMING
	} Timing;

	Brake brake;
	BatteryType batteryType;
	CutoffMode cutoffMode;
	CutoffThreshold cutoffThreshold;
	StartMode startMode;
	Timing timing;

	EscConfiguration(){
		brake = BRAKE_OFF;
		batteryType = LIPO;
		cutoffMode = HARD_CUTOFF;
		cutoffThreshold = MEDIUM_THRESHOLD;
		startMode = SOFT_START;
		timing = LOW_TIMING;
	}
};

#endif
