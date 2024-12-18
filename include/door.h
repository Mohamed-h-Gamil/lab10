#ifndef _DOOR_H_
#define _DOOR_H_

// definitions
#define DOOR_PIN 6
#define CLOSE_POS 0
#define OPEN_POS 90


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