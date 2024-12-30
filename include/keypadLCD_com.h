#ifndef _KEYPADLCD_COM_H_
#define _KEYPADLCD_COM_H_

#define MAX_TRIALS 3    // define maximum number of wrong passcode trials here
#define I2C_LCD         // unComment if using i2c lcd
#ifdef I2C_LCD
#define LCD_I2C_ADDR 0x27
#endif
#define LCD_ROWS 2      // define number of rows in the lcd here
#define LCD_COLS 16     // define number of columns in the lcd here

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include "door.h"
#include "passcode.h"
#include "tamper_detection.h"
#include "alarm.h"
#include "pir.h"

// Keypad setup
extern const byte ROWS;
extern const byte COLS;
extern char keys[4][4];
extern byte rowPins[4];
extern byte colPins[4];
extern Keypad keypad;

// LCD setup
#ifdef I2C_LCD
extern LiquidCrystal_I2C lcd;
#else
extern const byte rs, en, d4, d5, d6, d7;
extern LiquidCrystal lcd;
#endif
extern char buffer[MAX_PASSCODE_LENGTH];
extern byte counter;
extern byte trial_count;

// Functions Declarations
void lcd_init(void);
void display_input(const char x);
void get_input(void);
void clear(void);
bool checkInput(char x);



#endif
