#include <Servo.h>

#define PIN_WW 9
#define WW_MAX_ANGLE 135
#define WW_MIN_ANGLE 45
#define WW_MID_ANGLE 90
#define DELAY_MS	 2
#define END_DELAY_MS 250
#define INCR_ANGLE   1

Servo ww;
int angle = WW_MID_ANGLE;
int incr  = INCR_ANGLE;

void setup()
{
	ww.attach(PIN_WW);
	ww.write(WW_MID_ANGLE);
	delay(500);
}

void loop() {
	ww.write(angle);
	delay(DELAY_MS);
	angle += incr;

	if (angle >= WW_MAX_ANGLE) {
		incr = -1 * INCR_ANGLE;
		delay(END_DELAY_MS);
	}
	else if (angle <= WW_MIN_ANGLE) {
		incr = 1 * INCR_ANGLE;
		delay(END_DELAY_MS);
	}
}