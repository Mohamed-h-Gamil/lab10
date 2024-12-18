#include "passcode.h"

char Passcode[33];

void writePasscode()
{
    EEPROM.put(ADDRESS, PASSCODE);
}

void readPasscode()
{
    for (short i = 0; i < 33; i++)
    {
        Passcode[i] = EEPROM.read(55+i);
    }
    
}

bool checkPasscode(char x[33])
{
    readPasscode();
    return String(x).equals(String(Passcode));
}