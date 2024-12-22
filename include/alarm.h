#ifndef _ALARM_H_
#define _ALARM_H_

#include <Arduino.h>

#define BUZZER_PIN 13

void alarm_init();
void alarmON();
void alarmOFF();

#endif