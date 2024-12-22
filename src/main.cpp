#include <Arduino.h>
#include <avr/wdt.h>

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include <EEPROM.h>
#include "keypadLCD_com.h"
#include "passcode.h"

void setup()
{
    Serial.begin(9600);
    wdt_enable(WDTO_4S);    // Reliable Programming (fault tolerance)
    lcd_init();
    door_init();
    LDR_init();
    alarm_init();
    writePasscode();
}

void loop()
{
    get_input();
    detectTampering();
    wdt_reset();
}