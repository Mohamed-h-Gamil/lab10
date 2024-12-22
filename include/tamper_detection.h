#ifndef _TAMPER_DETECTION_H_
#define _TAMPER_DETECTION_H_

#include <Arduino.h>

//#define OPAMP_COMPARATOR    // comment if using LDR as analog input
#define LDR_PIN A4
#define LDR_THRESHOLD 64   //ldr input bin threshold ADC value


extern bool tampered;

void LDR_init();
unsigned short readLDR();
bool detectTampering();




#endif