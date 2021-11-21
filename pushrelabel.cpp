#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NUM_NEIGHBOURS 4

#define NUM_NODES 25
#define NUM_ROWS 5
#define NUM_COLS 5

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define SINK 4

struct node { // Pixel
    uint32_t height = 0;
    uint32_t excess_flow = 0;
    uint32_t pixel_value;
    int32_t curr_capacities[NUM_NEIGHBOURS + 1] = {-1}; // NESW edge current capacities: -1 == no edge
    int32_t capacities[NUM_NEIGHBOURS + 1] = {-1}; // NESW edge max capacities: -1 == no edge
};

struct terminal { // Source/Sink
    uint32_t height = 0;
    uint32_t excess_flow = 0;
    int32_t curr_capacities[NUM_NODES] = {-1};
    int32_t capacities[NUM_NODES] = {-1}; // max capacities to each node: -1 == no edge
};

// residual flow for each edge: [FROM][TO]
// Source_idx = NUM_NODES, Sink_idx = NUM_NODES + 1
int residual_flows[NUM_NODES+2][NUM_NODES+2] = {0};

node nodes[NUM_NODES]; // Pixels
terminal source; // Source has no bi-directional (startpoint) // ai
terminal sink; // Sink has no bi-directional (endpoint) // bi = 255 - ai

// Returns what node is overflowing
int overFlowNode() {
    for (int i = 0; i < NUM_NODES; i++) {
        if (nodes[i].excess_flow > 0) {
            return i;
        }
    }
    
    // No overflowing node
    return -1;
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
            if (nodes[node].height > nodes[neighbour_idx].height) {
                
            }
        } else { // Check neighbours for height values
            // Push only if curr_height is bigger than neighbour
            if (nodes[node].height > nodes[neighbour_idx].height) {
                
            }
        }
    }
}

void preflow() {
    // Sets height of source vertex == number of pixels + 2 (source&sink)
    source.height = NUM_NODES + 2;
    
    // Set current capacity and excess flow equal to capacity for edges from source
    for (int i = 0; i < NUM_NODES; i++) {
        source.curr_capacities[i] = source.capacities[i];
        nodes[i].excess_flow = source.capacities[i];
    }
}

int main(void) {

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
    
    //========== Push-relabel algorithm ====================
    preflow();
    
    // Loop until no pixel has overflowed
    while (overFlowNode() != -1) {
        int node = overFlowNode();
        if (!push(node)) {
            relabel(node);
        }
    }
    
    
}
