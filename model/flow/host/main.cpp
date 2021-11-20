#include "../../common/m5ops.h"
#include "../defines.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

volatile uint8_t *top = (uint8_t *)0x2f000000;
volatile uint32_t *arg1 = (uint32_t *)0x2f000001;
volatile uint32_t *arg2 = (uint32_t *)0x2f000009;
volatile uint32_t *arg3 = (uint32_t *)0x2f000011;
volatile uint32_t *arg4 = (uint32_t *)0x2f000019;
volatile uint32_t *arg5 = (uint32_t *)0x2f000021;
volatile uint32_t *arg6 = (uint32_t *)0x2f000029;
volatile uint32_t *arg7 = (uint32_t *)0x2f000031;
volatile uint32_t *arg8 = (uint32_t *)0x2f000039;

struct node { // Pixel
    int32_t capacities[NUM_NEIGHBOURS] = {-1}; // NESW edge capacities 
    int32_t costs[NUM_NEIGHBOURS] = {-1}; // NESW edge costs
};

struct terminal { // Source/Sink
    int32_t costs[NUM_NODES] = {-1};
};

int main(void) {
    node nodes[25];
    terminal source;
    terminal sink;

    m5_reset_stats();


    // Starts top
    *top = 1;
    while (*top != 0)
    ;
         

    m5_dump_stats();
    m5_exit();
}
