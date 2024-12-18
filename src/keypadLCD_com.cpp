#include "keypadLCD_com.h"


// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {A3, A2, A1, A0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD setup
const byte rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char buffer[33] = {0};
byte counter = 0;
byte trial = 0;
bool isBlocked = false;


void lcd_init(void)
{
    lcd.begin(16,2);
    lcd.setCursor(0, 1);
    lcd.print("Enter Passcode");
}


void display_input(const char x)
{
    lcd.setCursor(counter%16, counter/16);
    lcd.print(x);
}


void clear(void)
{
    memset((char *)buffer, 0, 32);
    counter = 0;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter Passcode");
}


bool checkInput(const char x)
{
    return (x>='0' && x<='9') || x=='A' || x=='B' || x=='C' || x=='D';
}


void get_input(void)
{
    char x = keypad.getKey();
    if (!isBlocked && x)
    {
        if (isLocked)
        {
            if (x == '#')
            {
                if (checkPasscode(buffer))
                {
                    open_door();
                    clear();
                    lcd.clear();
                    lcd.setCursor(0, 1);
                    lcd.print("WELLCOME");
                }
                else
                {
                    close_door();
                    clear();
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("ACCESS DENIED");
                    
                    trial++;
                    if (trial >= MAX_TRIALS)
                    {
                        isBlocked = true;
                    }
                    lcd.setCursor(1, 1);
                    lcd.print(MAX_TRIALS - trial);
                    lcd.setCursor(3,1);
                    lcd.print("trials left");
                }
            }
            else if (x == '*')
            {
                clear();
            }
            else if (checkInput(x) && counter < 32)
            {
                if (!counter)
                    lcd.clear();

                buffer[counter] = x;
                display_input(x);
                counter++;
            }
            else
            {
                // Handle invalid input (e.g., leƩers or exceeding code length)
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("Invalid input");
                delay(1000);
                clear();
                // resetCodeEntry();
            }
        }
        else
        {
            close_door();
            clear();
        }
    }   
}
