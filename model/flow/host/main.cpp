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
    int32_t curr_capacities[NUM_NEIGHBOURS + 1] = {-1}; // NESW edge current capacities: -1 == no edge
    int32_t capacities[NUM_NEIGHBOURS + 1] = {-1}; // NESW edge max capacities: -1 == no edge
};

struct terminal { // Source/Sink
    int32_t curr_capacities[NUM_NODES] = {-1};
    int32_t capacities[NUM_NODES] = {-1}; // max capacities to each node: -1 == no edge
};

int main(void) {
    node nodes[NUM_NODES];
    terminal source; // Source has no bi-directional (startpoint) // ai = 1 if white, 2 if black
    terminal sink; // Sink has no bi-directional (endpoint) // bi = 255 - ai

    //============= Graph Creation =====================

    // Create a clear division between pixels
    // Set half of pixels to white
    for (int i = 0; i < 13; i++) {
        nodes[i].pixel_value = 255; // 255 = white
    }
    
    // Set other half to black
    for (int i = 13; i < NUM_NODES; i++) { 
        nodes[i].pixel_value = 0; // 0 = black
    }
    
    // Set max capacities of each pixel's neighbours: 255 - |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            node curr_node = nodes[col + row*NUM_COLS];
            
            // Check W neighbour
            if (col != 0) {
                node w_neighbour = nodes[(col - 1) + row*NUM_COLS];
                curr_node.costs[West] = abs(curr_node.pixel_value - w_neighbour.pixel_value);
            }
            
            // Check N neighbour
            if (row != 0) {
                node n_neighbour = nodes[col + (row + 1)*NUM_COLS];
                curr_node.costs[North] = abs(curr_node.pixel_value - n_neighbour.pixel_value);
            }
            
            // Check E neighbour
            if (col != NUM_COLS - 1) {
                node e_neighbour = nodes[(col + 1) + (row - 1)*NUM_COLS];
                curr_node.costs[East] = abs(curr_node.pixel_value - w_neighbour.pixel_value);
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                node w_neighbour = nodes[(col - 1) + row*NUM_COLS];
                curr_node.costs[West] = abs(curr_node.pixel_value - w_neighbour.pixel_value);
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
