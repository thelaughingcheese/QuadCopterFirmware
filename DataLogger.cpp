#include "DataLogger.h"
#include <SPI.h>
#include <SD.h>
#include "Globals.h"

int buffIndex = 0;
float tbuff[DATALOGGERDATALENGTH];
float pbuff[DATALOGGERDATALENGTH];
float dbuff[DATALOGGERDATALENGTH];
QuadCopter* quadinst;

void LogData(){
	File myFile;
	if(!SD.begin()){
		DEBUGSPRINTLN("sdcard not found");
	}

	int logCount = 0;
	char logCountBuffer[16];

	myFile = SD.open("logCount.txt",FILE_READ);
	for(int i=0; i<16; i++){
		int buf = myFile.read();
		if(buf < 0) break;
		logCountBuffer[i] = buf;
	}
	myFile.close();
	SD.remove("LOGCOUNT.TXT");

	logCount = atoi(logCountBuffer);
	logCount++;

	myFile = SD.open("logCount.txt",FILE_WRITE);
	myFile.print(logCount);
	myFile.close();

	itoa(logCount,logCountBuffer,10);

	myFile = SD.open(logCountBuffer,FILE_WRITE);

	for(int i=0;i<DATALOGGERDATALENGTH;i++){
		myFile.print(tbuff[i],8); myFile.print(",");
		myFile.println(pbuff[i],8);
	}

	myFile.close();
}