#ifndef _PASSCODE_H_
#define _PASSCODE_H_

#include <EEPROM.h>
#include <Arduino.h>

#define MAX_PASSCODE_LENGTH 32
#define PASSCODE "1234ABCD\0"
#define ADDRESS 55

extern char Passcode[];

// Function Decleration
void writePasscode();
void readPasscode();
bool checkPasscode(char x[33]);


#endif
