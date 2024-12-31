#include "pir.h"
#include "keypadLCD_com.h"
#include "passcode.h"
#define BUZZER 13

volatile uint8_t seconds = 0;
volatile uint8_t overflow = 0;
volatile bool motionDetected = true;

void pir_init(){
    pinMode(PIR_PIN, INPUT); 
    digitalWrite(PIR_PIN, LOW);
}

void lowpower_init(){
    //  Save power by writing all Digital IO LOW
    for (int i = 0; i < 20; i++)
    {
        pinMode(i, OUTPUT);
    }
    
    // Disabling ADC (Reduces Power consumption Drastically)
    ADCSRA &= ~(1<<ADEN);

    // enable low power sleep mode
    SMCR |= (1<<SM1);
    SMCR |= (1<<SE);

    // Configure INT0 (D2) for rising edge detection
    EICRA |= (1 << ISC01) | (1 << ISC00); // Set ISC01 and ISC00 for rising edge
    EIMSK |= (1 << INT0);                 // Enable external interrupt INT0

    //delay(2000);  // Allow PIR sensor stabilization
    //Serial.println("System ready");
}

void Awake_timer_init(){
    // Configure timer 2 to disable sleep mode after AWAKE_TIME of inactivity
    // TCCR1B |= (1<<WGM12);   // CTC mode
    // OCR1A = 15624;  // 1 second on clk/1024 prescale
    seconds = 0;    // seconds counter
    overflow = 0;   // overflows counter
    TIMSK2 |= (1<<TOIE2);  // enable overflow interrupt

    TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);    // start timer with clk/1024 prescale
}

void reset_awake_timer()
{
    TCNT2 = 0;
    seconds = 0;
    overflow = 0;
}

void disable_awake_timer()
{
    TCCR2B &= ~(7); // disable the timer 
    TCNT2 = 0;
    seconds = 0;
    overflow = 0;
}

void enable_awake_timer()
{
    TCNT2 = 0;
    seconds = 0;
    overflow = 0;
    TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);    // start timer with clk/1024 prescale
}


// void sleepnow() {
//     // Disable peripherals
//     Serial.println("Entering sleep mode...");
//     lcd.noDisplay();
//     //ADCSRA &= ~(1 << ADEN);              // Disable ADC
    
//     // Configure sleep mode
//     cli();
//     set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//     // Almost all system clocks and peripherals are stopped, except for external interrupts, watchdog timer, or pin change interrupts.
//     sleep_enable();
    
//     // Enable interrupts and enter sleep mode
//     sei();
//     sleep_cpu();
    
//     // MCU is asleep and will wake up on interrupt
//     sleep_disable(); // Disable sleep after wake-up
//     //ADCSRA |= (1 << ADEN); // Re-enable ADC after waking up
//     lcd.display();         // Turn on the LCD
// }


void sleepnow() {
    // Disable peripherals
 //   Serial.println("Entering sleep mode...");
    lcd.noDisplay();
    lcd.noBacklight();
    //disable ADC
    #ifndef OPAMP_COMPARATOR
    ADCSRA &= ~(1 << ADEN); // Disable ADC before sleeping
    #endif

    // Disable Brown out detection unit (BOD) while sleeping
    MCUCR |= (3<<5);    // set both BODS and BODSE at the same time
    MCUCR = (MCUCR & ~(1<<BODSE)) | (1 << BODS);    // the set the BODS bit and clear the BODSE bit at the same time
    wdt_disable();
    __asm__ __volatile__("sleep");    //sleep_cpu();

    #ifndef OPAMP_COMPARATOR
    ADCSRA |= (1 << ADEN); // Re-enable ADC after waking up
    delay(200);
    #endif
    lcd.display();         // Turn on the LCD
}



ISR(INT0_vect) {
    //increment here 
    
    incrementIntrusion();
    Serial.println("Somebody Entered");
    wdt_enable(WDTO_4S);
    motionDetected = true;  // Set the flag when motion is detected
    EIMSK &= ~(1 << INT0);                 // disable external interrupt INT0
    reset_awake_timer();
    enable_awake_timer();
    
}


ISR(TIMER2_OVF_vect){
    overflow++;
    if (overflow == 60) // aproximately 1 second equals 60 overflows
    {
        if (seconds < AWAKE_TIME)
        {
            overflow = 0;
            seconds++;
          //  Serial.println(seconds);
        }
        else
        {
            motionDetected = false;
            EIMSK |= (1 << INT0);                 // Enable external interrupt INT0
            disable_awake_timer();
        }
    }
}
