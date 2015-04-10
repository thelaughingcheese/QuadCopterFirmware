#ifndef ESCSTARTUPMANAGER
#define ESCSTARTUPMANAGER

#include "ESC.h"
#include "EscConfiguration.h"

class EscStartupManager{
private:
	Esc* esc;
	long size;
public:
	EscStartupManager(Esc* escs, long n);
	void startupAllNormal();
	void setConfigurationAll(EscConfiguration config);
	void applyConfigurationAll();
};

#endif