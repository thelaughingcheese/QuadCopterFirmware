#include "ReceiverInput.h"
#include "Globals.h"

//pulse start
volatile unsigned long ch1Start = 0;
volatile unsigned long ch2Start = 0;
volatile unsigned long ch3Start = 0;
volatile unsigned long ch4Start = 0;
volatile unsigned long ch5Start = 0;
volatile unsigned long ch6Start = 0;
volatile unsigned long ch7Start = 0;
volatile unsigned long ch8Start = 0;
volatile unsigned long ch9Start = 0;

//input values
volatile long ch1 = 0;
volatile long ch2 = 0;
volatile long ch3 = 0;
volatile long ch4 = 0;
volatile long ch5 = 0;
volatile long ch6 = 0;
volatile long ch7 = 0;
volatile long ch8 = 0;
volatile long ch9 = 0;

volatile long channelCenterValue;

void setupReceiverInput(){
	pinMode(CH1PIN,INPUT);
	pinMode(CH2PIN,INPUT);
	pinMode(CH3PIN,INPUT);
	pinMode(CH4PIN,INPUT);
	pinMode(CH5PIN,INPUT);
	pinMode(CH6PIN,INPUT);
	pinMode(CH7PIN,INPUT);
	pinMode(CH8PIN,INPUT);
	//pinMode(CH9PIN,INPUT);

	attachInterrupt(CH1PIN,ch1Change,CHANGE);
	attachInterrupt(CH2PIN,ch2Change,CHANGE);
	attachInterrupt(CH3PIN,ch3Change,CHANGE);
	attachInterrupt(CH4PIN,ch4Change,CHANGE);
	attachInterrupt(CH5PIN,ch5Change,CHANGE);
	attachInterrupt(CH6PIN,ch6Change,CHANGE);
	attachInterrupt(CH7PIN,ch7Change,CHANGE);
	attachInterrupt(CH8PIN,ch8Change,CHANGE);
	//attachInterrupt(CH9PIN,ch9Change,CHANGE);
}

void calibrateChannelCenterValue(){
	delay(1000);
	long total = 0;
	for(int i=0; i<1000; i++){
		total += ROLL_CHANNEL + PITCH_CHANNEL + YAW_CHANNEL;
	}
	channelCenterValue = total / 3000;
}

void ch1Change(){
	if(digitalReadFast(CH1PIN)){ ch1Start=micros(); }
	else{ ch1=micros()-ch1Start; }
}
void ch2Change(){
	if(digitalReadFast(CH2PIN)){ ch2Start=micros(); }
	else{ ch2=micros()-ch2Start; }
}
void ch3Change(){
	if(digitalReadFast(CH3PIN)){ ch3Start=micros(); }
	else{ ch3=micros()-ch3Start; }
}
void ch4Change(){
	if(digitalReadFast(CH4PIN)){ ch4Start=micros(); }
	else{ ch4=micros()-ch4Start; }
}
void ch5Change(){
	if(digitalReadFast(CH5PIN)){ ch5Start=micros(); }
	else{ ch5=micros()-ch5Start; }
}
void ch6Change(){
	if(digitalReadFast(CH6PIN)){ ch6Start=micros(); }
	else{ ch6=micros()-ch6Start; }
}
void ch7Change(){
	if(digitalReadFast(CH7PIN)){ ch7Start=micros(); }
	else{ ch7=micros()-ch7Start; }
}
void ch8Change(){
	if(digitalReadFast(CH8PIN)){ ch8Start=micros(); }
	else{ ch8=micros()-ch8Start; }
}
/*void ch9Change(){
	if(digitalReadFast(CH9PIN)){ ch9Start=micros(); }
	else{ ch9=micros()-ch9Start; }
}*/