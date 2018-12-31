
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

void write_intensity(uint8_t addr, uint8_t intensity)
{
    fwrite(&addr,1,1,stdout);
    fwrite(&intensity,1,1,stdout);
    fflush(stdout);
}

void io_r_left_intensity(uint8_t intensity)
{
   write_intensity(0,intensity);
}

void io_g_left_intensity(uint8_t intensity)
{
   write_intensity(1,intensity);
}
void io_b_left_intensity(uint8_t intensity)
{
   write_intensity(2,intensity);
    
}
void io_r_right_intensity(uint8_t intensity)
{
   write_intensity(3,intensity);

}
void io_g_right_intensity(uint8_t intensity)
{
   write_intensity(4,intensity);
   
}
void io_b_right_intensity(uint8_t intensity)
{
   write_intensity(5,intensity);
    
}
void io_w_right_lowhi(uint8_t intensity)
{
   write_intensity(6,intensity);    
}

int main()
{
    lighthero_main();
}

