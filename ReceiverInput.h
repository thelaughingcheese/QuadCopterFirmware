#ifndef RECEIVERINPUT
#define RECEIVERINPUT

#include "Arduino.h"

#define CH1PIN 16
#define CH2PIN 17
#define CH3PIN 18
#define CH4PIN 19
#define CH5PIN 20

#define CH6PIN 21
#define CH7PIN 22
#define CH8PIN 23

//channel aliases
#define ROLL ch1
#define PITCH ch2
#define THROTTLE ch3
#define YAW ch4
#define MODE ch5

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

void setupReceiverInput();

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