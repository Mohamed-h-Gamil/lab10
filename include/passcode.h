#ifndef _PASSCODE_H_
#define _PASSCODE_H_

#include <EEPROM.h>
#include <Arduino.h>

#define MAX_PASSCODE_LENGTH 32
#define PASSCODE "1234ABCD\0"   // length less than MAX_PASSCODE_LENGTH

#define EEPROMMAX 1023
#define ADDRESS EEPROMMAX-MAX_PASSCODE_LENGTH
#define MillisPerHour 1000*60*60
#define HoursperDay 24
#define maxperbyte 255
extern char Passcode[];

// Function Decleration
void writePasscode();
void readPasscode();
bool checkPasscode(char x[33]);
void incrementIntrusion();
unsigned short getHourIndex();
void EEPROM_INIT();
#endif
