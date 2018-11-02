#include "lighthero.h"

led_state_t states[CTRL_COUNT];

void io_set_control(uint8_t signal, uint8_t intensity)
{
	switch(signal)
	{
		case CTRL_R_LEFT:
			io_r_left_intensity(intensity);
			break;
		case CTRL_G_LEFT:
			io_g_left_intensity(intensity);
			break;
		case CTRL_B_LEFT:
			io_b_left_intensity(intensity);
			break;
		case CTRL_R_RIGHT:
			io_r_right_intensity(intensity);
			break;
		case CTRL_G_RIGHT:
			io_g_right_intensity(intensity);
			break;
		case CTRL_B_RIGHT:
			io_b_right_intensity(intensity);
			break;
		case CTRL_W_RIGHT:
			io_w_right_lowhi(intensity / (255/2));
			break;
	}
}

void all_off()
{
	for(int i = 0; i < CTRL_COUNT; i++)
	{
		io_set_control(i,0);
	}
}

void all_on()
{
	for(int i = 0; i < CTRL_COUNT; i++)
	{
		io_set_control(i,255);
	}
}

void lighthero_main()
{
	do_justin_things();
}

void lighthero_do_decay(int ledindex)
{
	uint64_t mymicros = lighthero_micros();
	float val = states[ledindex].intensity;
	float dt = (mymicros - states[ledindex].setmicros);
	val *= exp(-1 * states[ledindex].decay * dt);
	states[ledindex].intensity = val;
	states[ledindex].setmicros = mymicros;
}


