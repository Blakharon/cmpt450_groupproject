#include "../../common/m5ops.h"
#include "../defines.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>

volatile uint8_t *top = (uint8_t *)0x2f000000;
volatile uint32_t *arg1 = (uint32_t *)0x2f000001;
volatile uint32_t *arg2 = (uint32_t *)0x2f000009;
volatile uint32_t *arg3 = (uint32_t *)0x2f000011;
volatile uint32_t *arg4 = (uint32_t *)0x2f000019;
volatile uint32_t *arg5 = (uint32_t *)0x2f000021;
volatile uint32_t *arg6 = (uint32_t *)0x2f000029;
volatile uint32_t *arg7 = (uint32_t *)0x2f000031;
volatile uint32_t *arg8 = (uint32_t *)0x2f000039;
volatile uint32_t *arg9 = (uint32_t *)0x2f000041;
volatile uint32_t *arg10 = (uint32_t *)0x2f000049;
volatile uint32_t *arg11 = (uint32_t *)0x2f000051;
volatile uint32_t *arg12 = (uint32_t *)0x2f000059;

// =========== Graph ================
TYPE* inputs =  (TYPE*)0x80100000;

// heights[NUM_NODES]
int32_t* heights = (int32_t*)0x80200000;
// excess_flows[NUM_NODES]
int32_t* excess_flows = (int32_t*)0x80230000;
// pixel_values[NUM_NODES]
int32_t* pixel_values = (int32_t*)0x80260000;
// nodes_curr_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)]
int32_t* nodes_curr_capacities = (int32_t*)0x80280000;
                               
// nodes_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)]
int32_t* nodes_capacities = (int32_t*)0x80350000;

// res_curr_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)]
int32_t* res_curr_capacities = (int32_t*)0x80480000;
                           
// Source has no bi-directional (startpoint) // ai
int32_t* source_height = (int32_t*)0x80500000;
                         
int32_t* source_excess_flow = (int32_t*)0x80530000;
                              
// source_curr_capacities[NUM_NODES]
int32_t* source_curr_capacities = (int32_t*)0x80560000;
                                          
// source_capacities[NUM_NODES]  
int32_t* source_capacities = (int32_t*)0x80590000;

// Sink has no bi-directional (endpoint) // bi
int32_t* sink_height = (int32_t*)0x805C0000;
                        
int32_t* sink_excess_flow = (int32_t*)0x805F0000;
                                          
// Residual Source: Nodes->source residual flow
// res_source_curr_capacities[NUM_NODES]
int32_t* res_source_curr_capacities = (int32_t*)0x80630000;


int main(void) {
    //============= Graph Creation =====================
    sink_height[0] = -1;
    // Initialize no edges to each node
    for (int i = 0; i < NUM_NODES; i++) {
        for (int j = 0; j < NUM_NEIGHBOURS + 1; j++) {
            nodes_curr_capacities[i*(NUM_NEIGHBOURS+1) + j] = -1;
            nodes_capacities[i*(NUM_NEIGHBOURS+1) + j] = -1;
            res_curr_capacities[i*(NUM_NEIGHBOURS+1) + j] = -1;
        }
    }

    // Set pixels to input values and residuals
    for (int i = 0; i < NUM_NODES; i++) {
        pixel_values[i] = inputs[i] >> 2;
    }
    
    // Set source->node capacities (ai) and residuals node->source capacities
    for (int i = 0; i < NUM_NODES; i++) {
        source_capacities[i] = inputs[i+NUM_NODES];
        
        source_curr_capacities[i] = 0;
        res_source_curr_capacities[i] = 0;
    }
    
    // Set max capacities of each pixel's neighbours: 255 - |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int curr_node_i = col + row*NUM_COLS;
            uint32_t curr_pixel_val = pixel_values[curr_node_i];
            #define abs(a) ((a)<0?(-a):(a))

            // Check W neighbour
            if (col != 0) {
                uint32_t w_pixel_val = pixel_values[(col - 1) + row*NUM_COLS];
                nodes_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + WEST] = 63 - abs(curr_pixel_val - w_pixel_val);
                nodes_curr_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + WEST] = 0;
            }
            
            // Check N neighbour
            if (row != 0) {
                uint32_t n_pixel_val = pixel_values[col + (row - 1)*NUM_COLS];
                nodes_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + NORTH] = 63 - abs(curr_pixel_val - n_pixel_val);
                nodes_curr_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + NORTH] = 0;
            }
            
            // Check E neighbour
            if (col != NUM_COLS - 1) {
                uint32_t e_pixel_val = pixel_values[(col + 1) + row*NUM_COLS];
                nodes_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + EAST] = 63 - abs(curr_pixel_val - e_pixel_val);
                nodes_curr_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + EAST] = 0;
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                uint32_t s_pixel_val = pixel_values[col + (row + 1)*NUM_COLS];
                nodes_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + SOUTH] = 63 - abs(curr_pixel_val - s_pixel_val);
                nodes_curr_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + SOUTH] = 0;
            }
            
            // Set capacity to sink (bi): 255 - ai
            nodes_curr_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + SINK] = 0;
            nodes_capacities[curr_node_i*(NUM_NEIGHBOURS+1) + SINK] = 255 - source_capacities[curr_node_i];
        }
    }

    // Set arguments e.g.,
    *top = 0x0;
    
    *arg1 = (uint32_t)(void *)heights;
    *arg2 = (uint32_t)(void *)excess_flows;
    *arg3 = (uint32_t)(void *)nodes_curr_capacities;
    *arg4 = (uint32_t)(void *)nodes_capacities;
    *arg5 = (uint32_t)(void *)res_curr_capacities;
    *arg6 = (uint32_t)(void *)source_height;
    *arg7 = (uint32_t)(void *)source_excess_flow;
    *arg8 = (uint32_t)(void *)source_curr_capacities;
    *arg9 = (uint32_t)(void *)source_capacities;
    *arg10 = (uint32_t)(void *)sink_height;
    *arg11 = (uint32_t)(void *)sink_excess_flow;
    *arg12 = (uint32_t)(void *)res_source_curr_capacities;
    
    *top = 1;
    while (*top != 0)
    ;

    printf("MaxFlow: %d                       \n", sink_excess_flow[0]);

    m5_dump_stats();
    m5_exit();
}
