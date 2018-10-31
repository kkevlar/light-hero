
#include <Arduino.h>

int pins[] = {2,3,5,6,9,10,11};

void setup()
{
	for(int i = 0; i < 7; i++)
	{
		pinMode(pins[i],OUTPUT);
	}
}

void all_off()
{
	for(int i = 0; i < 7; i++)
	{
		digitalWrite(pins[i],LOW);
	}
}

void all_on()
{
	for(int i = 0; i < 7; i++)
	{
		digitalWrite(pins[i],HIGH);
	}
}


void loop()
{

	all_off();
	delay(500);
	all_on();
	delay(2000);
	// all_off();

	// for(int i = 0; i < 20; i++)
	// {
	// 	digitalWrite(pins[0], HIGH);
	// 	digitalWrite(pins[6], HIGH);
	// 	delay(100);
	// 	all_off();
	// 	delay(150);
	// }

	// all_off();

	// delay(1000);

	// for(int i = 0; i < 7; i++)
	// {
	// 	all_off();
	// 	digitalWrite(pins[i],HIGH);
	// 	delay(400);
	// }
	// all_off();

	// delay(1000);

	// for(int i = 0; i < 7; i++)
	// {
	// 	digitalWrite(pins[i],HIGH);
	// 	delay(400);
	// }
	
	// all_off();

	// delay(2000);

	// for(int i = 0; i < 7; i++)
	// {
	// 	digitalWrite(pins[i],HIGH);
	// }

	// delay(1000);

	// all_off();

	// delay(3000);

}
