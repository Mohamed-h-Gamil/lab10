#include "keypadLCD_com.h"


// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {5, 4, 3, A5};
byte colPins[COLS] = {A3, A2, A1, A0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD setup
#ifdef I2C_LCD
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);
#else
const byte rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#endif
char buffer[MAX_PASSCODE_LENGTH] = {0};
byte counter = 0;
byte trial = 0;
bool isBlocked = false;

void lcd_init(void)
{
    #ifdef I2C_LCD
    lcd.init();
    //lcd.backlight();
    #else
    lcd.begin(LCD_COLS,LCD_ROWS);
    #endif
    lcd.setCursor(0, 1);
    lcd.print("Enter Passcode");
}


void display_input(const char x)
{
    lcd.setCursor(counter%LCD_COLS, counter/LCD_COLS);
    Serial.println(x);
    lcd.print(x);
}


void clear(void)
{
    memset((char *)buffer, 0, MAX_PASSCODE_LENGTH);
    counter = 0;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter Passcode");
}

// Reliable programming (fault tolerance)
bool checkInput(const char x)
{
    return (x>='0' && x<='9') || x=='A' || x=='B' || x=='C' || x=='D';
}


void get_input(void)
{
    char x = keypad.getKey();
    if (!tampered && !isBlocked && x)
    {
        reset_awake_timer();
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
            else if (checkInput(x) && counter < MAX_PASSCODE_LENGTH)
            {
                if (!counter)
                    lcd.clear();

                buffer[counter] = x;
                display_input(x);
                counter++;
            }
            else
            {
                // Handle invalid input (e.g., letters or exceeding code length)
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("Invalid input");
                delay(1000);
                clear();
            }
        }
        else
        {
            close_door();
            clear();
        }
    }
    else if (tampered)
    {
        close_door();
        alarmON();
        clear();
        lcd.setCursor(0, 1);
        lcd.print("TAMPERING Detected");
    }
}
