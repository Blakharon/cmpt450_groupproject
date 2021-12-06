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

struct pixel {
    uint32_t height = 0;
    uint32_t excess_flow = 0;
    uint32_t pixel_value;
    int32_t curr_capacities[NUM_NEIGHBOURS + 1]; // NESW edge current capacities: -1 == no edge
    int32_t capacities[NUM_NEIGHBOURS + 1]; // NESW edge max capacities: -1 == no edge
};

struct terminal { // Source/Sink
    uint32_t height = 0;
    uint32_t excess_flow = 0;
    int32_t curr_capacities[NUM_NODES];
    int32_t capacities[NUM_NODES]; // max capacities to each node: -1 == no edge
};

// residual flow for each edge: [FROM][TO]
// Source_idx = NUM_NODES, Sink_idx = NUM_NODES + 1
int residual_flows[(NUM_NODES+2) * (NUM_NODES+2)];

pixel nodes[NUM_NODES]; // Pixels
terminal source; // Source has no bi-directional (startpoint) // ai
terminal sink; // Sink has no bi-directional (endpoint) // bi = 255 - ai

// Returns what node is overflowing
int overFlowNode(int prev_node) {
    if (prev_node == -1) {
        prev_node = 0;
    }
    
    for (int i = (prev_node + 1) % NUM_NODES; i < NUM_NODES; i++) {
        if (nodes[i].excess_flow > 0) {
            return i;
        }
    }
    
    // No overflowing node
    return -1;
}

void updateResidualFlow(int node, int neighbour_idx, int flow) {

    if (neighbour_idx == -1) {    
        neighbour_idx = NUM_NODES + 1;
    }
    
    int residual_idx = (neighbour_idx * (NUM_NODES + 2)) + node;
    
    // Initialize residual edge
    if (residual_flows[residual_idx] == -1) {
        residual_flows[residual_idx] = 0;
    }
    
    residual_flows[residual_idx] -= flow;
}

void relabel(int node) {
    int min_height = INT_MAX;
    
    for (int i = 0; i < NUM_NEIGHBOURS + 1; i++) {
        int neighbour_idx; // -1 == sink
        if (i == 0) { // North neighbour
            neighbour_idx = node - NUM_COLS;
        } else if (i == 1) { // East neighbour
            neighbour_idx = node + 1;
        } else if (i == 2) { // South neighbour
            neighbour_idx = node + NUM_COLS;
        } else if (i == 3) { // West neighbour
            neighbour_idx = node - 1;
        } else { // Sink
            neighbour_idx = -1;
        }
        
        // If flow is == to capacity then skip relabelling
        if (nodes[node].curr_capacities[i] == nodes[node].capacities[i]) {
            continue;
        }
        
        if (neighbour_idx != -1) {
            if (nodes[neighbour_idx].height < min_height) {
                min_height = nodes[neighbour_idx].height;
                
                // Update height of node
                nodes[node].height = min_height + 1;
            }
        } else {
            if (sink.height < min_height) {
                min_height = sink.height;
                
                // Update height of node
                nodes[node].height = min_height + 1;
            }
        }
    }
}

bool push(int node) {
    // Go through all neighbours
    for (int i = 0; i < NUM_NEIGHBOURS + 1; i++) {
        // No neighbour
        if (nodes[node].capacities[i] == -1) {
            continue;
        }
    
        // Flow is maxed out already, can't push
        if (nodes[node].curr_capacities[i] == nodes[node].capacities[i]) {
            continue;
        }
        
        int neighbour_idx; // -1 == sink
        if (i == 0) { // North neighbour
            neighbour_idx = node - NUM_COLS;
        } else if (i == 1) { // East neighbour
            neighbour_idx = node + 1;
        } else if (i == 2) { // South neighbour
            neighbour_idx = node + NUM_COLS;
        } else if (i == 3) { // West neighbour
            neighbour_idx = node - 1;
        } else { // Sink
            neighbour_idx = -1;
        }
        
        // Check sink for height value
        if (neighbour_idx == -1) {
            // Push only if curr_height is bigger than sink
            if (nodes[node].height > sink.height) {
                int flow;
                int edge_flow_left = nodes[node].capacities[i] - nodes[node].curr_capacities[i];
                
                if (nodes[node].excess_flow > edge_flow_left) {
                    flow = edge_flow_left;
                } else {
                    flow = nodes[node].excess_flow;
                }
                
                // Reduce excess flow from node since we're moving it to neighbour
                nodes[node].excess_flow -= flow;
                
                // Increase excess flow for sink
                sink.excess_flow += flow;
                
                // Add flow to neighbour edge
                nodes[node].curr_capacities[i] += flow;
                
                // Update residual flow
                updateResidualFlow(node, neighbour_idx, flow);
                
                return true;
            }
        } else { // Check neighbours for height values
            // Push only if curr_height is bigger than neighbour
            if (nodes[node].height > nodes[neighbour_idx].height) {
                int flow;
                int edge_flow_left = nodes[node].capacities[i] - nodes[node].curr_capacities[i];
                
                if (nodes[node].excess_flow > edge_flow_left) {
                    flow = edge_flow_left;
                } else {
                    flow = nodes[node].excess_flow;
                }
                
                // Reduce excess flow from node since we're moving it to neighbour
                nodes[node].excess_flow -= flow;
                
                // Increase excess flow for neighbour
                nodes[neighbour_idx].excess_flow += flow;
                
                // Add flow to neighbour edge
                nodes[node].curr_capacities[i] += flow;
                
                // Update residual flow
                updateResidualFlow(node, neighbour_idx, flow);
                
                return true;
            }
        }
    }
    
    return false;
}

void preflow() {
    // Sets height of source vertex == number of pixels + 2 (source&sink)
    source.height = NUM_NODES + 2;
    
    for (int i = 0; i < NUM_NODES; i++) {
        // Set flow == capacity for edges from source
        source.curr_capacities[i] = source.capacities[i];
        // Set excess flow for node == capacity
        nodes[i].excess_flow = source.capacities[i];
        // Initialize residual for edge from node->source
        residual_flows[i*(NUM_NODES+2) + NUM_NODES] = 0;
    }
}

int main(void) {
    TYPE* base = (TYPE*) 0x80100000;

    for (int i = 0; i < 50; i++) {
        printf("%d   \n", base[i]);
    }

    pixel nodes[NUM_NODES];
    terminal source; // Source has no bi-directional (startpoint) // ai
    // terminal sink; // Sink has no bi-directional (endpoint) // bi = 255 - ai

    //============= Graph Creation =====================

    // Create a clear division between pixels
    // // Set half of pixels to white
    // for (int i = 0; i < 13; i++) {
    //     nodes[i].pixel_value = 200; // 255 = white
    // }
    
    // // Set other half to black
    // for (int i = 13; i < NUM_NODES; i++) { 
    //     nodes[i].pixel_value = 50; // 0 = black
    // }

    // Set pixels to input values
    for (int i = 0; i < 25; i++) {
        nodes[i].pixel_value = base[i] >> 2;
    }
    
    // Set source->node capacities (ai) 
    for (int i = 0; i < NUM_NODES; i++) {
        // if (nodes[i].pixel_value == 255) { // white
        //     source.capacities[i] = 255;
        // } else if (nodes[i].pixel_value == 0) { // black
        //     source.capacities[i] = 0;
        // } else {
        //     source.capacities[i] = 2;
        // }
        source.capacities[i] = base[i+25];
        
        source.curr_capacities[i] = 0;
    }
    
    // Set max capacities of each pixel's neighbours: 255 - |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int curr_node_i = col + row*NUM_COLS;
            pixel& curr_node = nodes[curr_node_i];
            
            #define abs(a) ((a)<0?(-a):(a))

            // Check W neighbour
            if (col != 0) {
                pixel w_neighbour = nodes[(col - 1) + row*NUM_COLS];
                curr_node.capacities[WEST] = 63 - abs(curr_node.pixel_value - w_neighbour.pixel_value);
                curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check N neighbour
            if (row != 0) {
                pixel n_neighbour = nodes[col + (row - 1)*NUM_COLS];
                curr_node.capacities[NORTH] = 63 - abs(curr_node.pixel_value - n_neighbour.pixel_value);
                curr_node.curr_capacities[NORTH] = 0;
            }
            
            // Check E neighbour
            if (col != NUM_COLS - 1) {
                pixel e_neighbour = nodes[(col + 1) + row*NUM_COLS];
                curr_node.capacities[EAST] = 63 - abs(curr_node.pixel_value - e_neighbour.pixel_value);
                curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                pixel s_neighbour = nodes[col + (row + 1)*NUM_COLS];
                curr_node.capacities[SOUTH] = 63 - abs(curr_node.pixel_value - s_neighbour.pixel_value);
            }
            
            // Set capacity to sink (bi): 255 - ai
            curr_node.capacities[SINK] = 255 - source.capacities[curr_node_i];
        }
    }
    
    //========== Push-relabel algorithm ====================
    preflow();
    
    // Loop until no pixel has overflowed
    int prev_node = -1;
    while (overFlowNode(prev_node) != -1) {
        int node = overFlowNode(prev_node);
        if (!push(node)) {
            relabel(node);
        }
        
        prev_node = node;
    }
    
    for (int i = 0; i < NUM_NODES; i++) {
        printf("excess flow %d: %d\n", i, nodes[i].excess_flow);
        printf("max capacity to sink %d: %d\n", i, nodes[i].capacities[SINK]);
        printf("pixel value %d: %d\n", i, nodes[i].pixel_value);
    }
    printf("Max flow: %d\n", sink.excess_flow);

    m5_reset_stats();
    //================================ Start accelerator ==========================

    TYPE *pl = base;

    // Set arguments e.g.,
    *top = 0x0;
    *arg1 = (uint32_t)(void *)pl;
    
    *top = 1;
    while (*top != 0)
    ;

    printf("%d   \n", *pl); 

    m5_dump_stats();
    m5_exit();
}
