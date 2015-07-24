
#ifndef DATALOGGER
#define DATALOGGER

#include "QuadCopter.h"""

#define DATALOGGERDATALENGTH 4000
extern int buffIndex;
extern float tbuff[DATALOGGERDATALENGTH];
extern float pbuff[DATALOGGERDATALENGTH];
extern float dbuff[DATALOGGERDATALENGTH];
extern QuadCopter* quadinst;

void LogData();

#endif