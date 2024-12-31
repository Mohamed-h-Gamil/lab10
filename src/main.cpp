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
#include <SoftwareSerial.h>

// Define Bluetooth RX/TX pins for SoftwareSerial
#define BT_RX 10
#define BT_TX 11

// Create SoftwareSerial instance for Bluetooth
SoftwareSerial BTSerial(BT_RX, BT_TX);
// Global or extern variable from your passcode logic

void setup()
{
    Serial.begin(9600);
       // === Added for Bluetooth ===
    // Initialize SoftwareSerial to 9600 (default for HC-05/HC-06)
    BTSerial.begin(9600);

    wdt_enable(WDTO_4S);    // Reliable Programming (fault tolerance)
    lowpower_init();
    EEPROM_INIT();
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

