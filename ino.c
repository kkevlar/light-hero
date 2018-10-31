
#include <Arduino.h>

int pins = {2,3,5,6,9,10,11};

void setup()
{
	for(int i = 0; i < sizeof(pins); i++)
	{
		pinMode(i,OUTPUT);
	}
}

void all_off()
{
	for(int i = 0; i < sizeof(pins); i++)
	{
		digitalWrite(i,LOW);
	}
}

void loop()
{
	all_off();
	delay(1000);

	for(int i = 0; i < sizeof(pins); i++)
	{
		all_off();
		digitalWrite(i,HIGH);
		delay(400);
	}
	all_off();

	delay(1000);

	for(int i = 0; i < sizeof(pins); i++)
	{
		digitalWrite(i,HIGH);
		delay(400);
	}
	
	all_off();

	delay(2000);

	for(int i = 0; i < sizeof(pins); i++)
	{
		digitalWrite(i,HIGH);
	}

	delay(1000);

	all_off();

	delay(1000);
	
}

