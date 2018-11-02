
#include "justin.h"

void do_justin_things()
{
	lighthero_init();
	while (1)
	{
		all_off();
		sleep_ms(500);
		all_on();
		sleep_ms(2000);
		all_off();

		for(int i = 0; i < 20; i++)
		{
			io_set_control(CTRL_R_LEFT, INTENSITY_MAX);
			io_set_control(CTRL_W_RIGHT, INTENSITY_MAX);
			sleep_ms(100);
			all_off();
			sleep_ms(150);
		}

		all_off();

		sleep_ms(1000);

		for(int i = 0; i < 7; i++)
		{
			all_off();
			io_set_control(i,INTENSITY_MAX);
			sleep_ms(400);
		}
		all_off();

		sleep_ms(1000);

		for(int i = 0; i < 7; i++)
		{
			io_set_control(i,INTENSITY_MAX);
			sleep_ms(400);
		}
		
		all_off();

		sleep_ms(2000);

		for(int i = 0; i < 7; i++)
		{
			io_set_control(i,INTENSITY_MAX);
		}

		sleep_ms(1000);

		all_off();

		sleep_ms(3000);
	}
}

void sleep_ms(int ms)
{
	lighthero_sleep_micros(1000 * ms)
}

