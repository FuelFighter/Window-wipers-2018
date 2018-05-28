#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define PWM_TOP 6061
#define SERVO_MIDDLE_us 1500e-6
#define SERVO_MAX_us    1800e-6  // abs max is 2200e-6
#define SERVO_MIN_us    1200e-6  // abs min is  800e-6
#define FREQ            330
#define PIN_RESET_bm    (1<<PB4)  // is pin PB4 / digitalPin12

// THIS CODE IS FOR THE SERVO MOTOR
// POWER HD-1235MG

int main() {
    DDRB |= (1<<PB1);  // PWM for servo
    DDRB &= ~PIN_RESET_bm;  // pin for reset set as input


    // set top to 6061 <=> 330 Hz
    ICR1 = PWM_TOP;

    // 90 deg  -  step 3000
    OCR1A = ICR1 * (SERVO_MIDDLE_us * FREQ);

    TCCR1A |= (1<<WGM11) | (1<<COM1A1);
    TCCR1B |= (1<<WGM13) | (1<<WGM12);
    TCCR1B |= (1<<CS11);   // 8 prescalar


    int incr = 1;
    while (1) {
        if (abs(OCR1A - ICR1 * (SERVO_MIDDLE_us * FREQ)) <= 4)  // is close to the middle
            _delay_ms(500);

        OCR1A += incr;
        _delay_us(700);

        if (OCR1A >= ICR1 * (SERVO_MAX_us * FREQ)) {
            incr = -1;
            _delay_ms(500);
        }
        else if (OCR1A <= ICR1 * (SERVO_MIN_us * FREQ)) {
            incr = 1;
            _delay_ms(500);
        }
    }

    return 0;
}