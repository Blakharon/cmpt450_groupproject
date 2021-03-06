#include "../hw_defines.h"

void pushrelabel(
    int32_t* heights, 
    int32_t* excess_flows, 
    int32_t* nodes_curr_capacities,
    int32_t* nodes_capacities,
    int32_t* res_curr_capacities,
    int32_t* source_height,
    int32_t* source_excess_flow,
    int32_t* source_curr_capacities,
    int32_t* source_capacities,
    int32_t* sink_height,
    int32_t* sink_excess_flow,
    int32_t* res_source_curr_capacities)
{
    //========== Push-relabel algorithm ====================

    //===================== Preflow() ====================
    // Sets height of source vertex == number of pixels + 2 (source&sink)
    source_height[0] = NUM_NODES + 2;
    
    for (int i = 0; i < NUM_NODES; i++) {
        // Set flow == capacity for edges from source
        source_curr_capacities[i] = source_capacities[i];
        res_source_curr_capacities[i] = source_capacities[i];
        // Set excess flow for node == capacity
        excess_flows[i] = source_capacities[i];
    }

    //=================== End of Preflow() ====================
    
    //================ initial overFlowNode() =========================
    int32_t node;
    for (int32_t i = 0; i < NUM_NODES; i++) {
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
    
    while (node != -1) {
        int32_t pushed = 0;
        //============================ Push() ========================
        int32_t continue_count = 0;

        // Try pushing to sink first
        if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK] < nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK]) {
            int32_t flow;
            int32_t edge_flow_left = nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK] - nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK];
            
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
            
            // If we actually pushed to the sink, return true
            if (flow > 0) {
                pushed = 1;
            }
        }

        if (pushed != 1) {
            // Go through all neighbours of node except sink
            for (int32_t i = 0; i < NUM_NEIGHBOURS; i++) {
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
                
                int32_t neighbour_idx;
                if (i == 0) { // North neighbour
                    neighbour_idx = node - NUM_COLS;
                } else if (i == 1) { // East neighbour
                    neighbour_idx = node + 1;
                } else if (i == 2) { // South neighbour
                    neighbour_idx = node + NUM_COLS;
                } else { // West neighbour
                    neighbour_idx = node - 1;
                }
                
                int32_t neighbour_height = heights[neighbour_idx];
                
                // Check neighbours for height values
                // Push only if curr_height is bigger than neighbour
                if (heights[node] > neighbour_height) {
                    int32_t flow;
                    int32_t edge_flow_left = nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] - nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + i];
                    
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
                    int32_t residual_neighbour;
                    residual_neighbour = i^0x2;
                    
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
                
                for (int32_t i = 0; i < NUM_NEIGHBOURS; i++) {
                    // No neighbour
                    if (nodes_capacities[node*(NUM_NEIGHBOURS+1) + i] == -1) {
                        continue_count++;
                        continue;
                    }
                    
                    int32_t neighbour_idx;
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
                    
                    int32_t neighbour_height = heights[neighbour_idx];
                    
                    // Check neighbours for height values
                    // Push only if curr_height is bigger than neighbour
                    if (heights[node] > neighbour_height) {
                        int32_t flow;
                        int32_t edge_flow_left = res_curr_capacities[node*(NUM_NEIGHBOURS+1) + i];
                        
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
                int32_t flow;
                int32_t edge_flow_left = res_source_curr_capacities[node];
                
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
                int32_t min_height = 999999999;
                int32_t continue_count = 0;
                int32_t relabelled;
                relabelled = 0;
                
                if (nodes_curr_capacities[node*(NUM_NEIGHBOURS+1) + SINK] != nodes_capacities[node*(NUM_NEIGHBOURS+1) + SINK]) {
                    // Update height of node
                    heights[node] = sink_height[0] + 1;
                    
                    relabelled = 1; //Relabelled the node to 1 higher than sink since there's space to push there
                }
                
                if (relabelled != 1) {
                    min_height = 999999999;
                    // Check for capacities to neighbours and relabel them if there is space
                    for (int32_t i = 0; i < NUM_NEIGHBOURS; i++) {
                        int32_t neighbour_idx;
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
                    
                        for (int32_t i = 0; i < NUM_NEIGHBOURS; i++) {
                            int32_t neighbour_idx;
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
        
        for (int32_t i = 0; i < NUM_NODES; i++) {
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
}
