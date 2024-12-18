#include "door.h"

Servo door;
bool isLocked;

void door_init()
{
    door.attach(DOOR_PIN);
    close_door();
    isLocked = true;
}

void open_door()
{
    door.write(OPEN_POS);
    isLocked = false;
}

void close_door()
{
    door.write(CLOSE_POS);
    isLocked = true;
}