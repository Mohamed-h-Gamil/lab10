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



void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
    wdt_enable(WDTO_4S);    // Reliable Programming (fault tolerance)
    lowpower_init();
    lcd_init();
    door_init();
    LDR_init();
    alarm_init();
    writePasscode();
    pir_init();
    Awake_timer_init();
    sei();
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
    wdt_reset();
}

