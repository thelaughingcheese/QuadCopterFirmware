/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Teensy 3.1, Platform=avr, Package=teensy
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __ARM_MK20dx256__
#define __ARM_MK20DX256__
#define ARDUINO 106
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 96000000
#define USB_SERIAL_HID
#define LAYOUT_US_ENGLISH
#define __cplusplus
#define GCC_VERSION 40804
#define ARDUINO_ARCH_AVR
#define ARDUINO_AVR_TEENSY31
#define __MK20DX256__
#define TEENSYDUINO 122
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

typedef void *__builtin_va_list;
#define __builtin_va_start
#define __builtin_va_end
//#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int

#define NEW_H
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}
#include <arduino.h>
#undef F
#define F(string_literal) ((const PROGMEM char *)(string_literal))
#undef PSTR
#define PSTR(string_literal) ((const PROGMEM char *)(string_literal))
#undef cli
#define cli()
#define pgm_read_byte(address_short)
#define pgm_read_word(address_short)
#define pgm_read_word2(address_short)
#define digitalPinToPort(P)
#define digitalPinToBitMask(P) 
#define digitalPinToTimer(P)
#define analogInPinToBit(P)
#define portOutputRegister(P)
#define portInputRegister(P)
#define portModeRegister(P)
#include <QuadCopterFirmware.ino>
#include <Accelerometer.cpp>
#include <Accelerometer.h>
#include <AttitudeMeasurement.cpp>
#include <AttitudeMeasurement.h>
#include <Barometer.cpp>
#include <Barometer.h>
#include <DataLogger.cpp>
#include <DataLogger.h>
#include <Esc.cpp>
#include <Esc.h>
#include <EscConfiguration.h>
#include <EscStartupManager.cpp>
#include <EscStartupManager.h>
#include <FlightController.cpp>
#include <FlightController.h>
#include <Globals.h>
#include <Gps.h>
#include <Gyroscope.cpp>
#include <Gyroscope.h>
#include <I2cDevice.cpp>
#include <I2cDevice.h>
#include <LowPassDerivativeFilter.cpp>
#include <LowPassDerivativeFilter.h>
#include <LowPassSensorFilter.h>
#include <Magnetometer.cpp>
#include <Magnetometer.h>
#include <PidController.cpp>
#include <PidController.h>
#include <QuadCopter.cpp>
#include <QuadCopter.h>
#include <ReceiverInput.cpp>
#include <ReceiverInput.h>
#include <ServoModified.cpp>
#include <ServoModified.h>
#include <WireModified.cpp>
#include <WireModified.h>
#include <tests.cpp>
#include <tests.h>
#endif
