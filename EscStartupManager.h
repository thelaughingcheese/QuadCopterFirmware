#ifndef ESCSTARTUPMANAGER
#define ESCSTARTUPMANAGER

#include "ESC.h"
#include "EscConfiguration.h"

class EscStartupManager{
private:
	Esc* esc;
	long size;
	EscConfiguration config;

	void throttleAllMin();
	void throttleAllMax();
public:
	EscStartupManager(Esc* escs, long n);
	void startupAllNormal();
	void applyRange();
	void setConfigurationAll(EscConfiguration cfg);
	void applyConfigurationAll();
};

#endif
