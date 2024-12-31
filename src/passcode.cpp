#include "passcode.h"

char Passcode[33];
SHA256 hash;
byte hashResult[SHA256::HASH_SIZE];


bool Reliable()    // Reliable Programming (fault tolerance)
{
    return (MAX_PASSCODE_LENGTH < 1024 && ADDRESS >= 0 && ADDRESS < (1024-MAX_PASSCODE_LENGTH) && strlen(PASSCODE) < MAX_PASSCODE_LENGTH);
}

void writePasscode()
{
    if (Reliable())   
    {
        EEPROM.put(ADDRESS, PASSCODE);
    }
}

void readPasscode()
{
    if (Reliable())
    {
        for (short i = 0; i <= MAX_PASSCODE_LENGTH; i++)
        {
            Passcode[i] = EEPROM.read(ADDRESS+i);
        }
    }
}

bool checkPasscode(char x[33])
{
    readPasscode();
    return String(x).equals(String(Passcode));
}

void calcHASH(){
    hash.reset();
    hash.update(PASSCODE, sizeof(PASSCODE));
    hash.finalize(hashResult, sizeof(hashResult));
}