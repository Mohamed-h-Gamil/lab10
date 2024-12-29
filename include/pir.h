#ifndef _PIR_H_
#define _PIR_H_

#define PIR_PIN 2 // INT 0
#define AWAKE_TIME  3   // no activity awake time in seconds

#include <avr/sleep.h>  // for sleep modes
#include <avr/interrupt.h>  // for interrupts
#include <avr/wdt.h>
#include <Arduino.h>

extern volatile uint8_t seconds;
extern volatile uint8_t overflow;
extern volatile bool motionDetected;

void pir_init();
void sleepnow();
void lowpower_init();
void Awake_timer_init();
void reset_awake_timer();
void disable_awake_timer();
void enable_awake_timer();
#endif