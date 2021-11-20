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
    int32_t pixel_value;
    int32_t curr_capacities[NUM_NEIGHBOURS] = {-1}; // NESW edge current capacities: -1 == no edge
    int32_t capacities[NUM_NEIGHBOURS] = {-1}; // NESW edge max capacities: -1 == no edge
    int32_t costs[NUM_NEIGHBOURS] = {-1}; // NESW edge costs: -1 == no edge
};

struct terminal { // Source/Sink
    int32_t costs[NUM_NODES] = {-1}; // costs to each node: -1 == no edge
};

int main(void) {
    node nodes[25];
    terminal source;
    terminal sink;

    // Create a clear division between pixels
    // Set half of pixels to white
    for (int i = 0; i < 13; i++) {
        nodes[i].pixel_value = 255; // 255 = white
    }
    
    // Set other half to black
    for (int i = 13; i < 25; i++) { 
        nodes[i].pixel_value = 0; // 0 = black
    }
    
    // Set costs of each pixel's neighbours: |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            node curr_node = nodes[col + row*5];
            
            // Check W neighbour
            if (col != 0) {
                
            }
            
            // Check N neighbour
            if (row != 0) {
            
            }
            
            // Check E neighbour
            if (col != 4) {
            
            }
            
            // Check S neighbour
            if (row != 4) {
            
            }
        }
    }

    m5_reset_stats();

    // Starts top
    *top = 1;
    while (*top != 0)
    ;

    m5_dump_stats();
    m5_exit();
}
