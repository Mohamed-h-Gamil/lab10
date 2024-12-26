#include "pir.h"
#include "keypadLCD_com.h"

void pir_init(){
    pinMode(PIR_PIN, INPUT); 
    digitalWrite(PIR_PIN, LOW);
    // Configure INT0 (D2) for rising edge detection
    EICRA |= (1 << ISC01) | (1 << ISC00); // Set ISC01 and ISC00 for rising edge
    EIMSK |= (1 << INT0);                 // Enable external interrupt INT0
    sei();
    Serial.println("System ready");
    delay(2000);  // Allow PIR sensor stabilization
    
}



void sleepnow() {
    // Disable peripherals
    Serial.println("Entering sleep mode...");
    lcd.noDisplay();
    //ADCSRA &= ~(1 << ADEN);              // Disable ADC
    
    // Configure sleep mode
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    // Almost all system clocks and peripherals are stopped, except for external interrupts, watchdog timer, or pin change interrupts.
    sleep_enable();
    
    // Enable interrupts and enter sleep mode
    sei();
    sleep_cpu();
    
    // MCU is asleep and will wake up on interrupt
    sleep_disable(); // Disable sleep after wake-up
    //ADCSRA |= (1 << ADEN); // Re-enable ADC after waking up
    lcd.display();         // Turn on the LCD
}

