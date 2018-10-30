#ifndef LIGHTHERO_H
#define LIGHTHERO_H

#define LED_CONTROL_SIGNALS 7

struct _light_hero_states_
{
	uint16_t intensity[LED_CONTROL_SIGNALS]; 
};
typedef struct _light_hero_states_ light_hero_states_t;

void light_hero_init();
void light_hero_sleep_micros(uint32_t micros);
uint64_t light_hero_micros();

#endif
