
#include "justin.h"

void left_on(float half_life_seconds)
{
	lighthero_set_pulse(CTRL_R_LEFT, half_life_seconds);
	lighthero_set_pulse(CTRL_G_LEFT, half_life_seconds);
	lighthero_set_pulse(CTRL_B_LEFT, half_life_seconds);
}

void right_on(float half_life_seconds)
{
	lighthero_set_pulse(CTRL_R_RIGHT, half_life_seconds);
	lighthero_set_pulse(CTRL_G_RIGHT, half_life_seconds);
	lighthero_set_pulse(CTRL_B_RIGHT, half_life_seconds);
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

	float bps = 60.0/60.0;

	float spb = 1/bps;

	uint64_t micros_per_beat = spb*1000*1000*.5;
	float normal_pulse = 0.0050;

	lighthero_set_value(0,0);
	lighthero_set_value(1,0);
	lighthero_set_value(2,0);
	lighthero_set_value(3,0);
	lighthero_set_value(4,0);
	lighthero_set_value(5,0);
	lighthero_set_value(6,0);

	while (1)
	{
		
		left_on(normal_pulse);
		refresh_for_awhile(micros_per_beat);
		lighthero_set_pulse(CTRL_B_LEFT, normal_pulse);
		refresh_for_awhile(micros_per_beat);
		right_on(normal_pulse);
		refresh_for_awhile(micros_per_beat);
		lighthero_set_pulse(CTRL_R_RIGHT, normal_pulse);
		refresh_for_awhile(micros_per_beat);
	}
}

