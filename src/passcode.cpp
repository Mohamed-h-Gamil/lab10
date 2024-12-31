#include "passcode.h"


char Passcode[MAX_PASSCODE_LENGTH+1];
//EEPROM INIT
void EEPROM_INIT(){
    for (int EEPROMindex = 0 ; EEPROMindex<HoursperDay;EEPROMindex++){
        EEPROM.write(EEPROMindex,0);
    }

}
bool Reliable()    // Reliable Programming (fault tolerance)
{
    return (MAX_PASSCODE_LENGTH < EEPROMMAX+1 && ADDRESS >= 0 && ADDRESS < (EEPROMMAX+1-MAX_PASSCODE_LENGTH) && strlen(PASSCODE) < MAX_PASSCODE_LENGTH);
}
unsigned short getHourIndex()
{
    return (millis()/MillisPerHour)%HoursperDay;
}
void incrementIntrusion(){

  unsigned short index = getHourIndex();
  unsigned char Intrusions =EEPROM[index];
  if (Intrusions<maxperbyte){
  EEPROM.write(index,Intrusions+1);}
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