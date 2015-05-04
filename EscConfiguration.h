#ifndef ESCCONFIGURATION
#define ESCCONFIGURATION

class EscConfiguration{
private:
public:
	typedef enum{
		ON,
		OFF
	} Brake;
	typedef enum{
		LIPO,
		NICD
	} BatteryType;
	typedef enum{
		SOFT,
		CUTOFF
	} CutoffMode;
	typedef enum{
		LOW,
		MEDIUM,
		HIGH
	} CutoffThreshold;
	typedef enum{
		NORMAL,
		SOFT,
		SUPERSOFT
	} StartMode;
	typedef enum{
		LOW,
		MEDIUM,
		HIGH
	} Timing;

	Brake brake;
	BatteryType batteryType;
	CutoffMode cutoffMode;
	CutoffThreshold cutoffThreshold;
	StartMode startmode;
	Timing timing;

	EscConfiguration(){
		brake = OFF;
		batteryType = LIPO;
		cutoffMode = CUTOFF;
		cutoffThreshold = MEDIUM;
		startmode = SOFT;
		timing = LOW;
	}
};

#endif
