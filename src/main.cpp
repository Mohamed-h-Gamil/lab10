#include <Arduino.h>

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include <EEPROM.h>
// Keypad and LCD setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(12, 11, 10, 5, 4, 3);

// Servo setup
Servo myServo;
const int servoPin = 8;

// Access code and security seƫngs
const int codeLength = 4;
char correctCode[codeLength + 1] = "1234";
char enteredCode[codeLength + 1];
int codeIndex = 0;
bool isLocked = true;

// EEPROM addresses for code storage
const int codeAddress = 0;

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);
    myServo.attach(servoPin);

    // Load code from EEPROM

    // loadCodeFromEEPROM();

    // lock();
}

void loop()
{
    char key = keypad.getKey();

    if (key)
    {
        if (key == '#')
        {
            // checkCode();
        }
        else if (key == '*')
        {
            // resetCodeEntry();
        }
        else if (key >= '0' && key <= '9' && codeIndex < codeLength)
        {
            // appendCode(key);
        }
        else
        {
            // Handle invalid input (e.g., leƩers or exceeding code length)
            lcd.setCursor(0, 1);
            lcd.print("Invalid input");
            delay(1000);
            // resetCodeEntry();
        }
    }
}