
#include "justin.h"

void left_on(float half_life_seconds)
{
	lighthero_set_pulse(CTRL_R_LEFT, 255, half_life_seconds);
	lighthero_set_pulse(CTRL_G_LEFT, 255, half_life_seconds);
	lighthero_set_pulse(CTRL_B_LEFT, 255, half_life_seconds);
}

void right_on(float half_life_seconds)
{
	lighthero_set_pulse(CTRL_R_RIGHT, 255, half_life_seconds);
	lighthero_set_pulse(CTRL_G_RIGHT, 255, half_life_seconds);
	lighthero_set_pulse(CTRL_B_RIGHT, 255, half_life_seconds);
	// lighthero_set_pulse(CTRL_W_RIGHT, half_life_seconds);
}

void refresh_for_awhile(uint64_t length)
{
	uint8_t refreshed = 0;
	uint64_t mymicros = lighthero_micros();
	uint64_t startmicros = lighthero_micros();

	mymicros += length;
	while(mymicros > lighthero_micros())
	{
		for(int i = 0; i < CTRL_COUNT; i++)
			lighthero_do_decay(i);
		// lighthero_flush();
		if(!refreshed && lighthero_micros() - startmicros > length / 2)
		{
			refreshed = 1;
			// lighthero_swap_sides();
		}

		lighthero_sleep_micros(50);
	}
}

void do_justin_things()
{
	lighthero_init();
	Serial.begin(9600);

	float bps = 60.0/60.0;

	float spb = 1/bps;

	uint64_t micros_per_beat = spb*1000*1000*.5;
	float normal_pulse = 0.0050;
	// float normal_pulse = 0.120;

	lighthero_set_value(0,0);
	lighthero_set_value(1,0);
	lighthero_set_value(2,0);
	lighthero_set_value(3,0);
	lighthero_set_value(4,0);
	lighthero_set_value(5,0);
	lighthero_set_value(6,0);

	while (1)
	{
		
	if (Serial.available() >0) {
      char c = Serial.read();
      if(c >= '0' && c <= '6')
      {
      	c -= '0';
      	lighthero_set_pulse(c, 255, normal_pulse);
		refresh_for_awhile(micros_per_beat);
      }
    } 
		
	}
}

