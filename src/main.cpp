#include <Arduino.h>

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include <EEPROM.h>
#include "keypadLCD_com.h"
#include "passcode.h"

// // Servo setup
// Servo myServo;
// const int servoPin = 8;

// // Access code and security seƫngs
// const int codeLength = 4;
// char correctCode[codeLength + 1] = "1234";
// char enteredCode[codeLength + 1];
// int codeIndex = 0;
// bool isLocked = true;

// // EEPROM addresses for code storage
// const int codeAddress = 0;


void setup()
{
    Serial.begin(9600);
    lcd_init();
    door_init();
    writePasscode();
}

void loop()
{
    get_input();
}