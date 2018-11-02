#ifndef LIGHTHERO_H
#define LIGHTHERO_H

#define CTRL_COUNT 7

#define CTRL_R_LEFT 0
#define CTRL_G_LEFT 1
#define CTRL_B_LEFT 2
#define CTRL_R_RIGHT 3
#define CTRL_G_RIGHT 4
#define CTRL_B_RIGHT 5
#define CTRL_W_RIGHT 6

#include "platform.h"
#include "justin.h"

struct _led_state_
{
	uint8_t signal;
	uint16_t intensity; 
	uint64_t setmicros;
	float decay; 
};
typedef struct _led_state_ led_state_t

void io_set_control(uint8_t signal, uint8_t intensity);
void all_off();
void all_on();
void lighthero_main();


#endif
