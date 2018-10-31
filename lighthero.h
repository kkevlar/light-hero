#ifndef LIGHTHERO_H
#define LIGHTHERO_H

#define LED_CONTROL_SIGNALS 7

#define CTRL_R_LEFT 0
#define CTRL_G_LEFT 1
#define CTRL_B_LEFT 2
#define CTRL_R_RIGHT 3
#define CTRL_G_RIGHT 4
#define CTRL_B_RIGHT 5
#define CTRL_W_RIGHT 6

#include "platform.h"

struct _light_hero_states_
{
	uint16_t intensity[LED_CONTROL_SIGNALS]; 
};
typedef struct _light_hero_states_ light_hero_states_t;

void io_set_control(uint8_t signal, uint8_t intensity);

#endif
