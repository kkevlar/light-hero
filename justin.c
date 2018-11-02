
#include "justin.h"

void left_on()
{
	lighthero_set_pulse(CTRL_R_LEFT);
	lighthero_set_pulse(CTRL_G_LEFT);
	lighthero_set_pulse(CTRL_B_LEFT);
}

void right_on()
{
	lighthero_set_pulse(CTRL_R_RIGHT);
	lighthero_set_pulse(CTRL_G_RIGHT);
	lighthero_set_pulse(CTRL_B_RIGHT);
	lighthero_set_pulse(CTRL_W_RIGHT);
}

void refresh_for_awhile()
{
	uint64_t mymicros = lighthero_micros();
	mymicros += 200*1000;
	while(mymicros > lighthero_micros())
	{
		for(int i = 0; i < CTRL_COUNT; i++)
			lighthero_do_decay(i);
		lighthero_flush();
	}
}

void do_justin_things()
{
	lighthero_init();
	while (1)
	{
		all_off();
		
		left_on();

		 refresh_for_awhile();

		all_off();
		right_on();

		 refresh_for_awhile();
	}
}

