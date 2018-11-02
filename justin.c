
#include "justin.h"

void do_justin_things()
{
	lighthero_init();
	while (1)
	{
		all_off();
		lighthero_sleep_micros(1000* 500);
		all_on();
		lighthero_sleep_micros(1000* 2000);
		all_off();

		for(int i = 0; i < 20; i++)
		{
			io_set_control(CTRL_R_LEFT, INTENSITY_MAX);
			io_set_control(CTRL_W_RIGHT, INTENSITY_MAX);
			lighthero_sleep_micros(1000* 100);
			all_off();
			lighthero_sleep_micros(1000* 150);
		}

		all_off();

		lighthero_sleep_micros(1000* 1000);

		for(int i = 0; i < 7; i++)
		{
			all_off();
			io_set_control(i,INTENSITY_MAX);
			lighthero_sleep_micros(1000* 400);
		}
		all_off();

		lighthero_sleep_micros(1000* 1000);

		for(int i = 0; i < 7; i++)
		{
			io_set_control(i,INTENSITY_MAX);
			lighthero_sleep_micros(1000* 400);
		}
		
		all_off();

		lighthero_sleep_micros(1000* 2000);

		for(int i = 0; i < 7; i++)
		{
			io_set_control(i,INTENSITY_MAX);
		}

		lighthero_sleep_micros(1000* 1000);

		all_off();

		lighthero_sleep_micros(1000* 3000);
	}
}

