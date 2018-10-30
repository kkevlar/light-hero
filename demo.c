
#include "demo.h"

struct timeval t1, t2;

void light_hero_init()
{
    gettimeofday(&t1, NULL);
}

void light_hero_sleep_micros(uint32_t micros)
{
    usleep(micros);
}

uint64_t light_hero_micros()
{
    double elapsed_time = 0;

    gettimeofday(&t2, NULL);   
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0 * 1000.0;
    elapsed_time += (t2.tv_usec - t1.tv_usec); 

    return elapsed_time;
}

int main()
{
    // for(int z = 0; z< 10; z++)
    // {
    //     for(int i = 0; i < 255; i++)
    //     {
    //         printf("%d,0,0,0,0,%d,%d\n",255-i,255-i,i);
    //         fflush(stdout);
    //         printf("%d,0,0,0,0,%d,%d\n",255-i,255-i,i);
    //         fflush(stdout);
    //         light_hero_sleep_micros(1000);
    //     }
    // }

    while(1)
    {   
        uint64_t i = light_hero_micros();
        printf("%d,0,0,0,0,%d,%d\n",(i/10000) % 255,(i/20000)%255,(i/10000)%255);
        fflush(stdout);
        light_hero_sleep_micros(100000);
    }
}

