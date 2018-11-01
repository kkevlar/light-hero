
#include "demo.h"


struct timeval t1, t2;

void lighthero_init()
{
    gettimeofday(&t1, NULL);
}

void lighthero_sleep_micros(uint32_t micros)
{
    usleep(micros);
}

uint64_t lighthero_micros()
{
    double elapsed_time = 0;

    gettimeofday(&t2, NULL);   
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0 * 1000.0;
    elapsed_time += (t2.tv_usec - t1.tv_usec); 

    return elapsed_time;
}

uint8_t intensities[CTRL_COUNT]; 

void reprint()
{
    printf("%d,%d,%d,%d,%d,%d,%d\n",
        intensities[0],
        intensities[1],
        intensities[2],
        intensities[3],
        intensities[4],
        intensities[5],
        intensities[6]
        );
}

void io_r_left_intensity(uint8_t intensity)
{
    intensities[0] = intensity;
    reprint();
}
void io_g_left_intensity(uint8_t intensity)
{
    intensities[1] = intensity;
    reprint();
}
void io_b_left_intensity(uint8_t intensity)
{
    intensities[2] = intensity;
    reprint();
}
void io_r_right_intensity(uint8_t intensity)
{
    intensities[3] = intensity;
    reprint();
}
void io_g_right_intensity(uint8_t intensity)
{
    intensities[4] = intensity;
    reprint();
}
void io_b_right_intensity(uint8_t intensity)
{
    intensities[5] = intensity;
    reprint();
}
void io_w_right_lowhi(uint8_t lowhi)
{
    intensities[6] = lowhi * 255;
    reprint();
}

int main()
{
    lighthero_main();
}

