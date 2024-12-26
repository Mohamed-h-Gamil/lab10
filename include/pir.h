#ifndef _PIR_H_
#define _PIR_H_

#define PIR_PIN 2 // INT 0
#include <avr/sleep.h>  // for sleep modes
#include <avr/interrupt.h>  // for interrupts
#include <Arduino.h>

void pir_init();
void sleepnow();

#endif