#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define PWM_TOP 6061
#define SERVO_MIDDLE_US 1500e-6
#define SERVO_MAX_US    2200e-6
#define SERVO_MIN_US    800e-6
#define FREQ 			330

// THIS CODE IS FOR THE SERVO MOTOR
// POWER HD-1235MG

int angleToUS(int angle) {
	// returns us
	return (int)(SERVO_MIN_US + (angle / 180.0) * (SERVO_MAX_US - SERVO_MIN_US));
}

void servoWrite(int us) {
	OCR1A = ICR1 * us * FREQ;
}

void servoWriteAngle(int angle) {
	int us = angleToUS(angle);
	servoWrite(us);
}

int main() {
	DDRB |= (1<<PB1);

	// set top to 6061 <=> 330 Hz
	ICR1 = PWM_TOP;

	// 90 deg  -  step 3000
	OCR1A = ICR1 * (SERVO_MIDDLE_US * FREQ);

	TCCR1A |= (1<<WGM11) | (1<<COM1A1);
	TCCR1B |= (1<<WGM13) | (1<<WGM12);
	TCCR1B |= (1<<CS11);   // 8 prescalar


	int incr = 1;
	int angle = 0;

	while (1) {
		//OCR1A = (int)pos;
		OCR1A += incr;
		_delay_us(700);
		// _delay_ms(1);

		if (OCR1A >= ICR1 * (1800e-6 * FREQ)) {
			incr = -1;
			_delay_ms(500);
		}
		else if (OCR1A <= ICR1 * (1200e-6 * FREQ)) {
			incr = 1;
			_delay_ms(500);
		}
	}

	return 0;
}