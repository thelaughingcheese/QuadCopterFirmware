#ifndef RECEIVERINPUT
#define RECEIVERINPUT

#include "Arduino.h"

#define CHCENTERVAL 1493
#define CHMAXVAL 430

#define CH1PIN 23
#define CH2PIN 22
#define CH3PIN 21
#define CH4PIN 20

#define CH5PIN 7
#define CH6PIN 8
#define CH7PIN 9
#define CH8PIN 10

//channel aliases
#define ROLL_CHANNEL (ch1-CHCENTERVAL)
#define PITCH_CHANNEL (ch2-CHCENTERVAL)
#define THROTTLE_CHANNEL (ch3-CHCENTERVAL)
#define YAW_CHANNEL (ch4-CHCENTERVAL)
#define MODE_CHANNEL (ch5-CHCENTERVAL)

//pulse start
extern volatile unsigned long ch1Start;
extern volatile unsigned long ch2Start;
extern volatile unsigned long ch3Start;
extern volatile unsigned long ch4Start;
extern volatile unsigned long ch5Start;
extern volatile unsigned long ch6Start;
extern volatile unsigned long ch7Start;
extern volatile unsigned long ch8Start;
//extern volatile long ch9Start;

//input values
extern volatile long ch1;
extern volatile long ch2;
extern volatile long ch3;
extern volatile long ch4;
extern volatile long ch5;
extern volatile long ch6;
extern volatile long ch7;
extern volatile long ch8;
//extern volatile long ch9;

extern volatile long channelCenterValue;

void setupReceiverInput();
void calibrateChannelCenterValue();

void ch1Change();
void ch2Change();
void ch3Change();
void ch4Change();
void ch5Change();
void ch6Change();
void ch7Change();
void ch8Change();
//void ch9Change();

#endif