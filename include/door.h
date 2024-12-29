#ifndef _DOOR_H_
#define _DOOR_H_

// definitions
#define DOOR_PIN 5
#define CLOSE_POS 0 // 0-180 degrees
#define OPEN_POS 90 // 0-180 degrees


// libraries
#include <Servo.h>

// external variables
extern Servo door;
extern bool isLocked;

// Functions declerations
void door_init();
void open_door();
void close_door();

#endif