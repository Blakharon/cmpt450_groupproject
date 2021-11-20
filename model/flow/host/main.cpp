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
    terminal source; // Source has no bi-directional (startpoint) // ai
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
    
    // Set source->node capacities (ai) 
    for (int i = 0; i < NUM_NODES; i++) {
        if (nodes[i].pixel_value == 255) { // white
            source.capacities[i] = 3;
        } else if (nodes[i].pixel_value == 0) { // black
            source.capacities[i] = 1;
        } else {
            source.capacities[i] = 2;
        }
        
        source.curr_capacities[i] = 0;
    }
    
    // Set max capacities of each pixel's neighbours: 255 - |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int curr_node_i = col + row*NUM_COLS;
            node curr_node = nodes[curr_node_i];
            
            // Check W neighbour
            if (col != 0) {
                node w_neighbour = nodes[(col - 1) + row*NUM_COLS];
                curr_node.capacities[WEST] = 255 - abs(curr_node.pixel_value - w_neighbour.pixel_value);
                curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check N neighbour
            if (row != 0) {
                node n_neighbour = nodes[col + (row + 1)*NUM_COLS];
                curr_node.capacities[North] = 255 - abs(curr_node.pixel_value - n_neighbour.pixel_value);
                curr_node.curr_capacities[NORTH] = 0;
            }
            
            // Check E neighbour
            if (col != NUM_COLS - 1) {
                node e_neighbour = nodes[(col + 1) + row*NUM_COLS];
                curr_node.capacities[EAST] = 255 - abs(curr_node.pixel_value - e_neighbour.pixel_value);
                curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                node s_neighbour = nodes[col + (row - 1)*NUM_COLS];
                curr_node.capacities[SOUTH] = 255 - abs(curr_node.pixel_value - s_neighbour.pixel_value);
            }
            
            // Set capacity to sink (bi): 255 - ai
            curr_node.capacities[SINK] = 255 - source.capacities[curr_node_i];
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
