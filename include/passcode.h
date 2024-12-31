#ifndef _PASSCODE_H_
#define _PASSCODE_H_

#include <EEPROM.h>
#include <Arduino.h>
#include <Crypto.h>
#include <SHA256.h>

#define MAX_PASSCODE_LENGTH 32
#define PASSCODE "1234ABCD\0"   // length less than MAX_PASSCODE_LENGTH
#define ADDRESS 55

extern char Passcode[];
extern byte hashResult[];

// Function Decleration
void writePasscode();
void readPasscode();
bool checkPasscode(char x[33]);
void calcHASH();


#endif
