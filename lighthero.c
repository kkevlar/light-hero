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
			io_w_right_lowhi(intensity);
			break;
	}
}

void all_off()
{
	for(int i = 0; i < CTRL_COUNT; i++)
	{
		lighthero_set_value(i, 0);
		lighthero_do_decay(i);

	}
}

void all_on()
{
	for(int i = 0; i < CTRL_COUNT; i++)
	{
		lighthero_set_value(i, 255);
		lighthero_do_decay(i);
	}
}

void lighthero_main()
{
	do_justin_things();
}

void lighthero_set_pulse(int ledindex, float half_life_seconds)
{
	uint64_t mymicros = lighthero_micros();
	states[ledindex].intensity = 255;
	states[ledindex].setmicros = mymicros;
	states[ledindex].decay = 0.69314718056;
	states[ledindex].decay /= half_life_seconds * 10e6;
}

void lighthero_set_value(int ledindex, int intensity)
{
	uint64_t mymicros = lighthero_micros();
	states[ledindex].intensity = intensity;
	states[ledindex].setmicros = mymicros;
	states[ledindex].decay = 0;
}

void lighthero_do_decay(int ledindex)
{
	float mymicros = lighthero_micros();
	float val = states[ledindex].intensity;
	float dt = states[ledindex].setmicros;
	dt = mymicros - dt;
	val = val * exp(-1 * states[ledindex].decay * dt);
	// states[ledindex].intensity = val;
	// states[ledindex].setmicros = mymicros;
	io_set_control(ledindex, val);

}

// void lighthero_flush()
// {
// 	for(int i = 0; i < CTRL_COUNT; i++)
// 	{
// 		io_set_control(i, states[i].intensity);
// 	}
// }


