#include <Arduino.h>
#include <avr/wdt.h>

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include <EEPROM.h>
#include "keypadLCD_com.h"
#include "passcode.h"

#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "pir.h"
volatile bool motionDetected = false;

void setup()
{
    Serial.begin(9600);
    //wdt_enable(WDTO_4S);    // Reliable Programming (fault tolerance)
    lcd_init();
    door_init();
    LDR_init();
    alarm_init();
    writePasscode();
    pir_init();
}

void loop()
{
    if (motionDetected){
        get_input();
        detectTampering();
    }
    else{
        sleepnow();
    }
    //wdt_reset();
}

ISR(INT0_vect) {
    motionDetected = true;  // Set the flag when motion is detected
    //EIMSK &= ~(1 << INT0);                 // disable external interrupt INT0
}
