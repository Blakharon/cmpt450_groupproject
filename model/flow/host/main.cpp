#include "../../common/m5ops.h"
#include "../defines.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>

volatile uint8_t *top = (uint8_t *)0x2f000000;
volatile uint32_t *arg1 = (uint32_t *)0x2f000001;
volatile uint32_t *arg2 = (uint32_t *)0x2f000009;
volatile uint32_t *arg3 = (uint32_t *)0x2f000017;
volatile uint32_t *arg4 = (uint32_t *)0x2f000025;
volatile uint32_t *arg5 = (uint32_t *)0x2f000033;
volatile uint32_t *arg6 = (uint32_t *)0x2f000041;
volatile uint32_t *arg7 = (uint32_t *)0x2f000049;
volatile uint32_t *arg8 = (uint32_t *)0x2f000057;
volatile uint32_t *arg9 = (uint32_t *)0x2f000065;
volatile uint32_t *arg10 = (uint32_t *)0x2f000073;
volatile uint32_t *arg11 = (uint32_t *)0x2f000081;
volatile uint32_t *arg12 = (uint32_t *)0x2f000089;
volatile uint32_t *arg13 = (uint32_t *)0x2f000097;
volatile uint32_t *arg14 = (uint32_t *)0x2f000105;
volatile uint32_t *arg15 = (uint32_t *)0x2f000113;

// =========== Graph ================
// Sink has no bi-directional (endpoint) // bi
//int32_t sink_excess_flow[1];
int32_t sink_curr_capacities[NUM_NODES];
int32_t sink_capacities[NUM_NODES];
// Residual Source: Nodes->source residual flow
int32_t res_source_curr_capacities[NUM_NODES];


TYPE* inputs =  (TYPE*)0x80100000;

// heights[NUM_NODES]
int32_t* heights = (int32_t*)0x80100000 + (50*sizeof(int32_t));
// excess_flows[NUM_NODES]
int32_t* excess_flows = (int32_t*)0x80100000 + (50*sizeof(int32_t)) + (NUM_NODES*sizeof(int32_t)*1);
// pixel_values[NUM_NODES]
int32_t* pixel_values = (int32_t*)0x80100000 + (50*sizeof(int32_t)) + (NUM_NODES*sizeof(int32_t)*2);
// nodes_curr_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)]
int32_t* nodes_curr_capacities = (int32_t*)0x80100000 + 
                                 (50*sizeof(int32_t)) + 
                                 (NUM_NODES*sizeof(int32_t)*3);
                               
// nodes_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)]
int32_t* nodes_capacities = (int32_t*)0x80100000 + 
                            (50*sizeof(int32_t)) + 
                            (NUM_NODES*sizeof(int32_t)*3) +
                            (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*1);
                            
// =========== Residual graph ===============

// res_curr_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)]
int32_t* res_curr_capacities = (int32_t*)0x80100000 + 
                               (50*sizeof(int32_t)) + 
                               (NUM_NODES*sizeof(int32_t)*3) +
                               (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2);
                           
// Source has no bi-directional (startpoint) // ai
int32_t* source_height = (int32_t*)0x80100000 + 
                          (50*sizeof(int32_t)) + 
                          (NUM_NODES*sizeof(int32_t)*3) +
                          (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*3);
                         
int32_t* source_excess_flow = (int32_t*)0x80100000 + 
                               (50*sizeof(int32_t)) + 
                               (NUM_NODES*sizeof(int32_t)*3) +
                               (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2) +
                               (sizeof(int32_t)*NUM_NODES*1);
                              
// source_curr_capacities[NUM_NODES]
int32_t* source_curr_capacities = (int32_t*)0x80100000 + 
                                  (50*sizeof(int32_t)) + 
                                  (NUM_NODES*sizeof(int32_t)*3) +
                                  (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2) +
                                  (sizeof(int32_t)*NUM_NODES*2);
                                          
// source_capacities[NUM_NODES]  
int32_t* source_capacities = (int32_t*)0x80100000 + 
                            (50*sizeof(int32_t)) + 
                            (NUM_NODES*sizeof(int32_t)*4) +
                            (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2) +
                            (sizeof(int32_t)*NUM_NODES*2);

// Sink has no bi-directional (endpoint) // bi
int32_t* sink_height = (int32_t*)0x80100000 + 
                        (50*sizeof(TYPE)) + 
                        (NUM_NODES*sizeof(TYPE)*5) +
                        (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(TYPE)*2) +
                        (sizeof(int32_t)*NUM_NODES*2);
                        
uint32_t* sink_excess_flow = (TYPE*)0x80100000 + 
                             (50*sizeof(TYPE)) + 
                             (NUM_NODES*sizeof(TYPE)*5) +
                             (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(TYPE)*2) +
                             (sizeof(int32_t)*NUM_NODES*3);
/*
// sink_curr_capacities[NUM_NODES]
int32_t* sink_curr_capacities = (int32_t*)0x80100000 + 
                                (50*sizeof(int32_t)) + 
                                (NUM_NODES*sizeof(int32_t)*5) +
                                (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2) +
                                (sizeof(int32_t)*4);
                                          
// sink_capacities[NUM_NODES]
int32_t* sink_capacities = (int32_t*)0x80100000 + 
                           (50*sizeof(int32_t)) + 
                           (NUM_NODES*sizeof(int32_t)*6) +
                           (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2) +
                           (sizeof(int32_t)*4);
// Residual Source: Nodes->source residual flow
// res_source_curr_capacities[NUM_NODES]
int32_t* res_source_curr_capacities = (int32_t*)0x80100000 + 
                                      (50*sizeof(int32_t)) + 
                                      (NUM_NODES*sizeof(int32_t)*7) +
                                      (NUM_NODES*(NUM_NEIGHBOURS+1)*sizeof(int32_t)*2) +
                                      (sizeof(int32_t)*4);
*/

// Returns what node is overflowing
int overFlowNode() {
    for (int i = 0; i < NUM_NODES; i++) {
        if (excess_flows[i] > 0) {
            return i;
        }
    }
    
    // No overflowing node
    return -1;
}

void relabel(int node) {
    int min_height = INT_MAX;
    int continue_count = 0;
    
    if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK] != nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK]) {
        // Update height of node
        heights[node] = sink_height[0] + 1;
        
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
        if (nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] == -1) {
            continue_count++;
            continue;
        }
        
        // If flow is == to capacity then skip relabelling
        if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + i] == nodes_capacities[node*(NUM_NEIGHBOURS+1) + i]) {
            continue_count++;
            continue;
        }
        
        if (heights[neighbour_idx] < min_height) {
            min_height = heights[neighbour_idx];
            
            // Update height of node
            heights[node] = min_height + 1;
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
            if (nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] == -1) {
                continue_count++;
                continue;
            }
            
            // If residual flows <= 0, either there is no residual edge or it is maxed out
            if (res_curr_capacities[node*(NUM_NEIGHBOURS+1) + i] <= 0) {
                continue_count++;
                continue;
            }
            
            if (heights[neighbour_idx] < min_height) {
                min_height = heights[neighbour_idx];
                
                // Update height of node
                heights[node] = min_height + 1;
            }
        }
    }
    
    // Residuals all full so change height to 1 higher than source
    if (continue_count == NUM_NEIGHBOURS) {
        heights[node] = source_height[0] + 1;
    }
}

void updateResidualFlow(int node, int neighbour, int flow) {
    //initialize residual edge
    if (res_curr_capacities[node*(NUM_NEIGHBOURS+1) + neighbour] == -1) {
        res_curr_capacities[node*(NUM_NEIGHBOURS+1) + neighbour] = 0;
    }

    res_curr_capacities[node*(NUM_NEIGHBOURS+1) + neighbour] += flow;
    //printf("Updated residual edge: %d\n", res_nodes[node].curr_capacities[neighbour]);
}

bool push(int node) {
    int continue_count = 0;

    // Try pushing to sink first
    if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK] < nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK]) {
        int flow;
        int edge_flow_left = nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK] - nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK];
        
        if (excess_flows[node] > edge_flow_left) {
            flow = edge_flow_left;
        } else {
            flow = excess_flows[node];
        }
        
        // Reduce excess flow from node since we're moving it to neighbour
        excess_flows[node] -= flow;
        
        // Increase excess flow for sink
        sink_excess_flow[0] += flow;
        
        // Add flow to sink edge
        nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK] += flow;
        
        //printf("Pushing to sink: %d\n", flow);
        
        // If we actually pushed to the sink, return true
        if (flow > 0) {
            return true;
        }
    }

    // Go through all neighbours of node except sink
    for (int i = 0; i < NUM_NEIGHBOURS; i++) {
        // No neighbour
        
        //printf("Neighbour %d curr/capacity: %d/%d\n", i, nodes[node].curr_capacities[i], nodes[node].capacities[i]);
        if (nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] == -1) {
            continue_count++;
            continue;
        }
    
        // Flow is maxed out already, can't push to this neighbour
        if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + i] == nodes_capacities[node*(NUM_NEIGHBOURS+1) + i]) {
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
        
        //printf("Trying to push to neighbour: %d\n", i);
        
        int neighbour_height = heights[neighbour_idx];
        //printf("Neighbour height: %d\n", neighbour_height);
        
        // Check neighbours for height values
        // Push only if curr_height is bigger than neighbour
        if (heights[node] > neighbour_height) {
            int flow;
            int edge_flow_left = nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] - nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + i];
            
            if (excess_flows[node] > edge_flow_left) {
                flow = edge_flow_left;
            } else {
                flow = excess_flows[node];
            }
            
            // Reduce excess flow from node since we're moving it to neighbour
            excess_flows[node] -= flow;
            
            // Increase excess flow for neighbour
            excess_flows[neighbour_idx] += flow;
            
            // Add flow to neighbour edge
            nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + i] += flow;
            
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
            
            //printf("Pushing flow: %d\n", flow);
            
            return true;
        }
    }
    
    // Flow has been maxed out on all edges, so try pushing in the residual graph
    //printf("Push continue count before residuals: %d\n", continue_count);
    if (continue_count == NUM_NEIGHBOURS) {
        continue_count = 0;
        
        for (int i = 0; i < NUM_NEIGHBOURS; i++) {
            //printf("Neighbour %d residual curr/capacity: %d/%d\n", i, res_nodes[node].curr_capacities[i], res_nodes[node].capacities[i]);
            // No neighbour
            if (nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] == -1) {
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
            if (res_curr_capacities[node*(NUM_NEIGHBOURS+1) + i] <= 0) {
                continue_count++;
                continue;
            }
            
            //printf("Trying to push to residual neighbour: %d\n", i);
            //printf("Residual neighbour currcapacity: %d\n", res_nodes[node].curr_capacities[i]);
            
            int neighbour_height = heights[neighbour_idx];
            //printf("Residual Neighbour height: %d\n", neighbour_height);
            
            // Check neighbours for height values
            // Push only if curr_height is bigger than neighbour
            if (heights[node] > neighbour_height) {
                int flow;
                int edge_flow_left = res_curr_capacities[node*(NUM_NEIGHBOURS+1) + i];
                
                if (excess_flows[node] > edge_flow_left) {
                    flow = edge_flow_left;
                } else {
                    flow = excess_flows[node];
                }
                
                // Reduce excess flow from node since we're moving it to neighbour
                excess_flows[node] -= flow;
                
                // Increase excess flow for neighbour
                excess_flows[neighbour_idx] += flow;
                
                // Add flow to neighbour edge
                res_curr_capacities[node*(NUM_NEIGHBOURS+1) + i] -= flow;
                //printf("Pushing residual flow: %d\n", flow);
                
                return true;
            }
        }
    }
    
    // Residual flows maxed out, push back to source
    if (continue_count == NUM_NEIGHBOURS) {
        int flow;
        int edge_flow_left = res_source_curr_capacities[node];
        
        if (excess_flows[node] > edge_flow_left) {
            flow = edge_flow_left;
        } else {
            flow = excess_flows[node];
        }
        
        // Reduce excess flow from node since we're moving it to neighbour
        excess_flows[node] -= flow;
        
        // Increase excess flow for sink
        source_excess_flow[0] += flow;
        
        // Add flow to sink edge
        res_source_curr_capacities[node] -= flow;
        
        //printf("Pushing back to source: %d\n", flow);
        // If we actually pushed to the sink, return true
        if (flow > 0) {
            return true;
        }
        
        //printf("Couldnt push back to source\n");
        //printf("Excess flow left: %d\n", nodes[node].excess_flow);
    }
    
    return false;
}

void preflow() {
    // Sets height of source vertex == number of pixels + 2 (source&sink)
    source_height[0] = NUM_NODES + 2;
    
    for (int i = 0; i < NUM_NODES; i++) {
        // Set flow == capacity for edges from source
        source_curr_capacities[i] = source_capacities[i];
        res_source_curr_capacities[i] = source_capacities[i];
        // Set excess flow for node == capacity
        excess_flows[i] = source_capacities[i];
        //printf("Starting excess flow %d: %d\n", i, nodes[i].excess_flow);
    }
}

int main(void) {
    //int base[NUM_NODES*2] = {0,127,127,127,0,127,195,195,195,127,127,195,255,195,127,127,195,195,195,127,0,127,127,127,0,
    //0,0,119,0,0,0,119,255,119,0,119,255,255,255,119,0,119,255,119,0,0,0,119,0,0};
    
    //int base[8] = {4,255,255,255,
    //    4,255,255,255};

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
            //printf("sink capacities: %d\n", 255 - source.capacities[curr_node_i]);
        }
    }
    
    //========== Push-relabel algorithm ====================
    preflow();
    
    // Loop until no pixel has overflowed
    while (overFlowNode() != -1) {
        int node = overFlowNode();
        //printf("\n\nnode: %d\n", node);
        //printf("height: %d\n", nodes[node].height);
        if (!push(node)) {
            relabel(node);
        }
    }
    
    
    printf("Max flow: %d\n", sink_excess_flow[0]);

    //================================ Start accelerator ==========================
    
    printf("%d   \n", sizeof(TYPE));
    heights[0] = 69;
    printf("%d   \n", sizeof(int32_t));

    // Set arguments e.g.,
    *top = 0x0;
    /*
    *arg1 = (uint32_t)(void *)heights;
    *arg2 = (uint32_t)(void *)excess_flows;
    *arg3 = (uint32_t)(void *)pixel_values;
    *arg4 = (uint32_t)(void *)nodes_curr_capacities;
    *arg5 = (uint32_t)(void *)nodes_capacities;
    *arg6 = (uint32_t)(void *)res_curr_capacities;
    *arg7 = (uint32_t)(void *)source_height;
    *arg8 = (uint32_t)(void *)source_excess_flow;
    *arg9 = (uint32_t)(void *)source_curr_capacities;
    *arg10 = (uint32_t)(void *)source_capacities;
    *arg11 = (uint32_t)(void *)sink_height;
    *arg12 = (uint32_t)(void *)sink_excess_flow;
    *arg13 = (uint32_t)(void *)sink_curr_capacities;
    *arg14 = (uint32_t)(void *)sink_capacities;
    *arg15 = (uint32_t)(void *)res_source_curr_capacities;
    */
    
    *top = 1;
    while (*top != 0)
    ;

    printf("%d   \n", heights[0]);

    m5_dump_stats();
    m5_exit();
}
