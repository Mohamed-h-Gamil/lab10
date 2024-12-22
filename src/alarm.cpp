#include "alarm.h"


void alarm_init()
{
    pinMode(BUZZER_PIN, OUTPUT);
    alarmOFF();
}


void alarmON()
{
    digitalWrite(BUZZER_PIN, HIGH);
}

void alarmOFF()
{
    digitalWrite(BUZZER_PIN, LOW);
}