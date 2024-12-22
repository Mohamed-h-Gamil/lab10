#include "tamper_detection.h"

bool tampered = false;

void LDR_init()
{
    pinMode(LDR_PIN, INPUT);
    tampered = false;
}

unsigned short readLDR()
{
    unsigned short light[3];    // take three readings - Reliable Programmin (fault tolerance)

    #ifdef OPAMP_COMPARATOR

    // for (int i = 0; i < 3; i++)
    // {
    //     light[i] = digitalRead(LDR_PIN);
    //     delay(50);
    // }

    // Loop unrolling (Reliable Programming (low power))
    light[0] = digitalRead(LDR_PIN);
    delay(50);
    light[1] = digitalRead(LDR_PIN);
    delay(50);
    light[2] = digitalRead(LDR_PIN);

    return light[0]^light[1]^light[2];  // XOR voting agorithm


    #else
    // for (int i = 0; i < 3; i++)
    // {
    //     light[i] = analogRead(LDR_PIN);
    //     delay(50);
    // }

    // Loop unrolling (Reliable Programming (low power))
    light[0] = analogRead(LDR_PIN);
    delay(50);
    light[1] = analogRead(LDR_PIN);
    delay(50);
    light[2] = analogRead(LDR_PIN);

    // Sort the light array using a simple comparison-based method (without looping (bubble sort))
    if (light[0] > light[1]) {
        unsigned short temp = light[0];
        light[0] = light[1];
        light[1] = temp;
    }
    if (light[1] > light[2]) {
        unsigned short temp = light[1];
        light[1] = light[2];
        light[2] = temp;
    }
    if (light[0] > light[1]) {
        unsigned short temp = light[0];
        light[0] = light[1];
        light[1] = temp;
    }

    return light[1];    // return the median value
    #endif
}


bool detectTampering()
{
    #ifdef OPAMP_COMPARATOR
    tampered = (bool)(readLDR()|tampered);
    return tampered;
    #else
    tampered = (bool)((readLDR() > (unsigned short)LDR_THRESHOLD)|tampered);
    return tampered;
    #endif
}

