#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <climits>

#define NUM_NEIGHBOURS 4

#define NUM_NODES 25
#define NUM_ROWS 5
#define NUM_COLS 5

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define SINK 4

// Graph
int32_t heights[NUM_NODES];
int32_t excess_flows[NUM_NODES];
int32_t pixel_values[NUM_NODES];
int32_t nodes_curr_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)];
int32_t nodes_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)];
// Residual graph
int32_t res_curr_capacities[NUM_NODES*(NUM_NEIGHBOURS+1)];
// Source has no bi-directional (startpoint) // ai
int32_t source_height[1];
int32_t source_excess_flow[1];
int32_t source_curr_capacities[NUM_NODES];
int32_t source_capacities[NUM_NODES];
// Sink has no bi-directional (endpoint) // bi
int32_t sink_height[1];
int32_t sink_excess_flow[1];
int32_t sink_curr_capacities[NUM_NODES];
int32_t sink_capacities[NUM_NODES];
// Residual Source: Nodes->source residual flow
int32_t res_source_curr_capacities[NUM_NODES];

/*
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
*/

/*
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
*/

/*
void updateResidualFlow(int node, int neighbour, int flow) {
    //initialize residual edge
    if (res_curr_capacities[node*(NUM_NEIGHBOURS+1) + neighbour] == -1) {
        res_curr_capacities[node*(NUM_NEIGHBOURS+1) + neighbour] = 0;
    }

    res_curr_capacities[node*(NUM_NEIGHBOURS+1) + neighbour] += flow;
}
*/

/*
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
        
        int neighbour_height = heights[neighbour_idx];
        
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
            
            return true;
        }
    }
    
    // Flow has been maxed out on all edges, so try pushing in the residual graph
    if (continue_count == NUM_NEIGHBOURS) {
        continue_count = 0;
        
        for (int i = 0; i < NUM_NEIGHBOURS; i++) {
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
            
            int neighbour_height = heights[neighbour_idx];
            
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
        
        // If we actually pushed to the sink, return true
        if (flow > 0) {
            return true;
        }
    }
    
    return false;
}
*/

/*
void preflow() {
    // Sets height of source vertex == number of pixels + 2 (source&sink)
    source_height[0] = NUM_NODES + 2;
    
    for (int i = 0; i < NUM_NODES; i++) {
        // Set flow == capacity for edges from source
        source_curr_capacities[i] = source_capacities[i];
        res_source_curr_capacities[i] = source_capacities[i];
        // Set excess flow for node == capacity
        excess_flows[i] = source_capacities[i];
    }
}
*/


int main(void) {
    int base[NUM_NODES*2] = {0,127,127,127,0,127,195,195,195,127,127,195,255,195,127,127,195,195,195,127,0,127,127,127,0,
    0,0,119,0,0,0,119,255,119,0,119,255,255,255,119,0,119,255,119,0,0,0,119,0,0};
    
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
        pixel_values[i] = base[i] >> 2;
    }
    
    // Set source->node capacities (ai) and residuals node->source capacities
    for (int i = 0; i < NUM_NODES; i++) {
        source_capacities[i] = base[i+NUM_NODES];
        
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
    
    //========== Push-relabel algorithm ====================

    //===================== Preflow() ====================
    //preflow();
    // Sets height of source vertex == number of pixels + 2 (source&sink)
    source_height[0] = NUM_NODES + 2;
    
    for (int i = 0; i < NUM_NODES; i++) {
        // Set flow == capacity for edges from source
        source_curr_capacities[i] = source_capacities[i];
        res_source_curr_capacities[i] = source_capacities[i];
        // Set excess flow for node == capacity
        excess_flows[i] = source_capacities[i];
    }
    
    for (int i = 0; i < NUM_NODES; i++) {
        printf("source_curr_capacities: %d\n", source_curr_capacities[i]);
    }
    
    //=================== End of Preflow() ====================
    
    //================ initial overFlowNode() =========================
    int node;
    for (int i = 0; i < NUM_NODES; i++) {
        if (excess_flows[i] > 0) {
            node = i;
            break;
        }
        
        // No overflowing node
        if (i == NUM_NODES - 1) {
            node = -1;
        }
    }
    //================== End of initial overFlowNode() =======================
    int nodes_used[3];
    //while (node != -1) {
    for (int i = 0; i < 3; i++) {
        nodes_used[i] = node;
        int pushed = 0;
        //============================ Push() ========================
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
                pushed = 1;
            }
        }

        if (pushed != 1) {
            // Go through all neighbours of node except sink
            for (int i = 0; i < NUM_NEIGHBOURS; i++) {
                // No neighbour
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
                
                int neighbour_height = heights[neighbour_idx];
                
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
                    
                    //================== updateResidualFlow() ======================
                    
                    //initialize residual edge
                    if (res_curr_capacities[neighbour_idx*(NUM_NEIGHBOURS+1) + residual_neighbour] == -1) {
                        res_curr_capacities[neighbour_idx*(NUM_NEIGHBOURS+1) + residual_neighbour] = 0;
                    }

                    res_curr_capacities[neighbour_idx*(NUM_NEIGHBOURS+1) + residual_neighbour] += flow;
                    
                    //=================== end of updateResidualFlow() ===================
                    
                    pushed = 1;
                    break;
                }
            }
        }
        
        if (pushed != 1) {
            // Flow has been maxed out on all edges, so try pushing in the residual graph
            if (continue_count == NUM_NEIGHBOURS) {
                continue_count = 0;
                
                for (int i = 0; i < NUM_NEIGHBOURS; i++) {
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
                    
                    int neighbour_height = heights[neighbour_idx];
                    
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
                        
                        pushed = 1;
                        break;
                    }
                }
            }
        }
        
        if (pushed != 1) {
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
                
                // If we actually pushed to the sink, return true
                if (flow > 0) {
                    pushed = 1;
                }
            }
        }

        //==================== End of Push() ========================
        if (pushed != 1) {
        
            //======================= Relabel() =========================
                int min_height = INT_MAX;
                int continue_count = 0;
                int relabelled;
                relabelled = 0;
                
                if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK] != nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK]) {
                    // Update height of node
                    heights[node] = sink_height[0] + 1;
                    
                    relabelled = 1; //Relabelled the node to 1 higher than sink since there's space to push there
                }
                
                if (relabelled != 1) {
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
            
            //====================== End of Relabel() ========================
        }
        
        
        //===================== overFlowNode() =========================
        
        for (int i = 0; i < NUM_NODES; i++) {
            if (excess_flows[i] > 0) {
                node = i;
                break;
            }
            
            // No overflowing node
            if (i == NUM_NODES - 1) {
                node = -1;
            }
        }
        
        //==================== End of overFlowNode() =======================
    }
    
    /*
    // Loop until no pixel has overflowed
    while (overFlowNode() != -1) {
        int node = overFlowNode();
        if (!push(node)) {
            relabel(node);
        }
    }
    */
    

    for (int i = 0; i < 3; i++) {
        printf("nodes: %d\n", nodes_used[i]);
    }
    
    printf("MaxFlow: %d\n", sink_excess_flow[0]);
}
