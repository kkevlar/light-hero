
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
	lighthero_set_pulse(CTRL_W_RIGHT, half_life_seconds);
}

void refresh_for_awhile()
{
	uint64_t mymicros = lighthero_micros();
	mymicros += .5*1000*1000;
	while(mymicros > lighthero_micros())
	{
		for(int i = 0; i < CTRL_COUNT; i++)
			lighthero_do_decay(i);
		lighthero_flush();
		lighthero_sleep_micros(2000);
	}
}

void do_justin_things()
{
	lighthero_init();
	while (1)
	{
		all_off();
		
		left_on(1);

		 refresh_for_awhile();

		all_off();
		right_on(1);

		 refresh_for_awhile();
	}
}

