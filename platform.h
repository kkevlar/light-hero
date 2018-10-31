#ifndef PLATFORM_H
#define PLATFORM_H

#include "demo.h"
// #include "ino.h"

void io_r_left_intensity(uint8_t intensity);
void io_g_left_intensity(uint8_t intensity);
void io_b_left_intensity(uint8_t intensity);
void io_r_right_intensity(uint8_t intensity);
void io_g_right_intensity(uint8_t intensity);
void io_b_right_intensity(uint8_t intensity);
void io_w_right_lowhi(bool lowhi);
void light_hero_init();
void light_hero_sleep_micros(uint32_t micros);
uint64_t light_hero_micros();

#endif
