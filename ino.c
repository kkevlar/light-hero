#include "ino.h"

uint8_t pwm_pins[] = {3,5,6,9,10,11};
uint8_t digital_pins[] = {2,13};

void lighthero_init()
{
	int i;

	for(i = 0; i < sizeof(pwm_pins)/sizeof(uint8_t); i++)
	{
		pinMode(pwm_pins[i], OUTPUT);
		digitalWrite(pwm_pins[i], LOW);
	}

	for(i = 0; i < sizeof(digital_pins)/sizeof(uint8_t); i++)
	{
		pinMode(digital_pins[i], OUTPUT);
		digitalWrite(digital_pins[i], LOW);
	}

 //    delay(1000);

 //    for(i = 0; i < sizeof(digital_pins)/sizeof(uint8_t); i++)
	// {
	// 	digitalWrite(digital_pins[i], HIGH);
	// 	delay(400);
	// 	digitalWrite(digital_pins[i], LOW);
	// 	delay(100);
	// }

	// for(i = 0; i < sizeof(pwm_pins)/sizeof(uint8_t); i++)
	// {
	// 	digitalWrite(pwm_pins[i], HIGH);
	// 	delay(400);
	// 	digitalWrite(pwm_pins[i], LOW);
	// 	delay(100);
	// }

	// delay(1000);
}

void lighthero_sleep_micros(uint32_t micros)
{
	delayMicroseconds(micros);
}

uint64_t lighthero_micros()
{
	return micros();
}

void io_r_left_intensity(uint8_t intensity)
{
	analogWrite(10, intensity);
}
void io_g_left_intensity(uint8_t intensity)
{
	analogWrite(11, intensity);
}
void io_b_left_intensity(uint8_t intensity)
{
	analogWrite(9, intensity);
}
void io_r_right_intensity(uint8_t intensity)
{
	analogWrite(6, intensity);
}
void io_g_right_intensity(uint8_t intensity)
{
	analogWrite(5, intensity);
}
void io_b_right_intensity(uint8_t intensity)
{
	analogWrite(3, intensity);
}
void io_w_right_lowhi(uint8_t lowhi)
{
    digitalWrite(2, lowhi);
}

void setup()
{
	lighthero_init();
	lighthero_main();
}

void loop()
{

}

