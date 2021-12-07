#include "../../common/m5ops.h"
#include "../defines.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>

volatile uint8_t *top = (uint8_t *)0x2f000000;
volatile struct teststruct *arg1 = (struct teststruct *)0x2f000001;

pixel nodes[NUM_NODES]; // Pixels
pixel res_nodes[NUM_NODES]; // Residual graph
terminal source; // Source has no bi-directional (startpoint) // ai
terminal sink; // Sink has no bi-directional (endpoint) // bi = 255 - ai
terminal res_source; // Nodes->source residual flow

// Returns what node is overflowing
int overFlowNode(int node) { 
    for (int i = 0; i < NUM_NODES; i++) {
        if (nodes[i].excess_flow > 0) {
            return i;
        }
    }
    
    // No overflowing node
    return -1;
}

void relabel(int node) {
    int min_height = INT_MAX;
    int continue_count = 0;
    
    if (nodes[node].curr_capacities[SINK] != nodes[node].capacities[SINK]) {
        // Update height of node
        nodes[node].height = sink.height + 1;
        
        return; //Relabelled the node to 1 higher than sink since there's space to push there
    }
    
    min_height = INT_MAX;
    
    // Check for capacities to neighbours and relabel them if there is space
    for (int i = 0; i < NUM_NEIGHBOURS; i++) {
        int neighbour_idx;
        if (i == 0) { // North neighbour
            neighbour_idx = node - NUM_COLS;
        } else if (i == 1) { // East neighbour
            neighbour_idx = node + 1;
        } else if (i == 2) { // South neighbour
            neighbour_idx = node + NUM_COLS;
        } else { // West neighbour
            neighbour_idx = node - 1;
        }
        
        // No neighbour
        if (nodes[node].capacities[i] == -1) {
            continue_count++;
            continue;
        }
        
        // If flow is == to capacity then skip relabelling
        if (nodes[node].curr_capacities[i] == nodes[node].capacities[i]) {
            continue_count++;
            continue;
        }
        
        if (nodes[neighbour_idx].height < min_height) {
            min_height = nodes[neighbour_idx].height;
            
            // Update height of node
            nodes[node].height = min_height + 1;
        }
    }
    
    // Capacites for all neighbours full, try residual graph
    if (continue_count == NUM_NEIGHBOURS) {
        continue_count = 0;
    
        for (int i = 0; i < NUM_NEIGHBOURS; i++) {
            int neighbour_idx;
            if (i == 0) { // North neighbour
                neighbour_idx = node - NUM_COLS;
            } else if (i == 1) { // East neighbour
                neighbour_idx = node + 1;
            } else if (i == 2) { // South neighbour
                neighbour_idx = node + NUM_COLS;
            } else { // West neighbour
                neighbour_idx = node - 1;
            }
            
            // No neighbour
            if (nodes[node].capacities[i] == -1) {
                continue_count++;
                continue;
            }
            
            // If residual flows <= 0, either there is no residual edge or it is maxed out
            if (res_nodes[node].curr_capacities[i] <= 0) {
                continue_count++;
                continue;
            }
            
            if (nodes[neighbour_idx].height < min_height) {
                min_height = nodes[neighbour_idx].height;
                
                // Update height of node
                nodes[node].height = min_height + 1;
            }
        }
    }
    
    // Residuals all full so change height to 1 higher than source
    if (continue_count == NUM_NEIGHBOURS) {
        nodes[node].height = source.height + 1;
    }
}

void updateResidualFlow(int node, int neighbour, int flow) {
    //initialize residual edge
    if (res_nodes[node].curr_capacities[neighbour] == -1) {
        res_nodes[node].curr_capacities[neighbour] = 0;
    }

    res_nodes[node].curr_capacities[neighbour] += flow;
}

bool push(int node) {
    int continue_count = 0;

    // Try pushing to sink first
    if (nodes[node].curr_capacities[SINK] < nodes[node].capacities[SINK]) {
        int flow;
        int edge_flow_left = nodes[node].capacities[SINK] - nodes[node].curr_capacities[SINK];
        
        if (nodes[node].excess_flow > edge_flow_left) {
            flow = edge_flow_left;
        } else {
            flow = nodes[node].excess_flow;
        }
        
        // Reduce excess flow from node since we're moving it to neighbour
        nodes[node].excess_flow -= flow;
        
        // Increase excess flow for sink
        sink.excess_flow += flow;
        
        // Add flow to sink edge
        nodes[node].curr_capacities[SINK] += flow;
        
        // If we actually pushed to the sink, return true
        if (flow > 0) {
            return true;
        }
    }

    // Go through all neighbours of node except sink
    for (int i = 0; i < NUM_NEIGHBOURS; i++) {
        // No neighbour
        if (nodes[node].capacities[i] == -1) {
            continue_count++;
            continue;
        }
    
        // Flow is maxed out already, can't push to this neighbour
        if (nodes[node].curr_capacities[i] == nodes[node].capacities[i]) {
            continue_count++;
            continue;
        }
        
        int neighbour_idx;
        if (i == 0) { // North neighbour
            neighbour_idx = node - NUM_COLS;
        } else if (i == 1) { // East neighbour
            neighbour_idx = node + 1;
        } else if (i == 2) { // South neighbour
            neighbour_idx = node + NUM_COLS;
        } else { // West neighbour
            neighbour_idx = node - 1;
        }
        
        int neighbour_height = nodes[neighbour_idx].height;
        
        // Check neighbours for height values
        // Push only if curr_height is bigger than neighbour
        if (nodes[node].height > neighbour_height) {
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
            int residual_neighbour;
            if (i == NORTH) {
                residual_neighbour = SOUTH;
            } else if (i == SOUTH) {
                residual_neighbour = NORTH;
            } else if (i == EAST) {
                residual_neighbour = WEST;
            } else {
                residual_neighbour = EAST;
            }
            updateResidualFlow(neighbour_idx, residual_neighbour, flow);
            
            return true;
        }
    }
    
    // Flow has been maxed out on all edges, so try pushing in the residual graph
    if (continue_count == NUM_NEIGHBOURS) {
        continue_count = 0;
        
        for (int i = 0; i < NUM_NEIGHBOURS; i++) {
            // No neighbour
            if (nodes[node].capacities[i] == -1) {
                continue_count++;
                continue;
            }
            
            int neighbour_idx;
            if (i == 0) { // North neighbour
                neighbour_idx = node - NUM_COLS;
            } else if (i == 1) { // East neighbour
                neighbour_idx = node + 1;
            } else if (i == 2) { // South neighbour
                neighbour_idx = node + NUM_COLS;
            } else { // West neighbour
                neighbour_idx = node - 1;
            }
            
            // Flow is maxed out already on residual or there is no residual, can't push to this neighbour
            if (res_nodes[node].curr_capacities[i] <= 0) {
                continue_count++;
                continue;
            }
            
            int neighbour_height = nodes[neighbour_idx].height;
            
            // Check neighbours for height values
            // Push only if curr_height is bigger than neighbour
            if (nodes[node].height > neighbour_height) {
                int flow;
                int edge_flow_left = res_nodes[node].curr_capacities[i];
                
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
                res_nodes[node].curr_capacities[i] -= flow;
                
                return true;
            }
        }
    }
    
    // Residual flows maxed out, push back to source
    if (continue_count == NUM_NEIGHBOURS) {
        int flow;
        int edge_flow_left = res_source.curr_capacities[node];
        
        if (nodes[node].excess_flow > edge_flow_left) {
            flow = edge_flow_left;
        } else {
            flow = nodes[node].excess_flow;
        }
        
        // Reduce excess flow from node since we're moving it to neighbour
        nodes[node].excess_flow -= flow;
        
        // Increase excess flow for sink
        source.excess_flow += flow;
        
        // Add flow to sink edge
        res_source.curr_capacities[node] -= flow;
        
        // If we actually pushed to the sink, return true
        if (flow > 0) {
            return true;
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
        res_source.curr_capacities[i] = source.capacities[i];
        // Set excess flow for node == capacity
        nodes[i].excess_flow = source.capacities[i];
    }
}

int main(void) {
    TYPE *base = (TYPE *)0x80100000;

    for (int i = 0; i < NUM_NODES*2; i++) {
        printf("%d   \n", base[i]);
    }

    //============= Graph Creation =====================
    
    sink.height = -1;
    // Initialize no edges to each node
    for (int i = 0; i < NUM_NODES; i++) {
        for (int j = 0; j < NUM_NEIGHBOURS + 1; j++) {
            nodes[i].curr_capacities[j] = -1;
            nodes[i].capacities[j] = -1;
            res_nodes[i].curr_capacities[j] = -1;
            res_nodes[i].capacities[j] = -1;
        }
    }

    // Set pixels to input values and residuals
    for (int i = 0; i < NUM_NODES; i++) {
        nodes[i].pixel_value = base[i] >> 2;
        res_nodes[i].pixel_value = base[i] >> 2;
    }
    
    // Set source->node capacities (ai) and residuals node->source capacities
    for (int i = 0; i < NUM_NODES; i++) {
        source.capacities[i] = base[i+NUM_NODES];
        res_source.capacities[i] = base[i+NUM_NODES];
        
        source.curr_capacities[i] = 0;
        res_source.curr_capacities[i] = 0;
    }
    
    // Set max capacities of each pixel's neighbours: 255 - |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int curr_node_i = col + row*NUM_COLS;
            pixel& curr_node = nodes[curr_node_i];
            pixel& curr_res_node = res_nodes[curr_node_i];
            
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
                curr_node.curr_capacities[EAST] = 0;
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                pixel s_neighbour = nodes[col + (row + 1)*NUM_COLS];
                curr_node.capacities[SOUTH] = 63 - abs(curr_node.pixel_value - s_neighbour.pixel_value);
                curr_node.curr_capacities[SOUTH] = 0;
            }
            
            // Set capacity to sink (bi): 255 - ai
            curr_node.curr_capacities[SINK] = 0;
            curr_node.capacities[SINK] = 255 - source.capacities[curr_node_i];
        }
    }
    m5_reset_stats();
    //========== Push-relabel algorithm ====================
    preflow();
    
    // Loop until no pixel has overflowed
    int node = 0;
    while (overFlowNode(node) != -1) {
        int node = overFlowNode(node);
        if (!push(node)) {
            relabel(node);
        }
    }
    
    
    printf("Max flow: %d\n", sink.excess_flow);

    //================================ Start accelerator ==========================

    TYPE base2 = 0x80200000;
    teststruct *pl = (teststruct *)base;
    pl->a = 69;
    pl->b = 70;

    // Set arguments e.g.,
    *top = 0x0;
    *arg1 = (uint32_t)(void *)pl;
    
    *top = 1;
    while (*top != 0)
    ;

    printf("%d   \n", pl->a); 
    printf("%d   \n", pl->b); 

    m5_dump_stats();
    m5_exit();
}
