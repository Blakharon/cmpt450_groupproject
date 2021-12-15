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

// struct node { // Pixel
//     uint32_t height = 0;
//     uint32_t pixel_value;
//     int32_t curr_capacities[NUM_NEIGHBOURS + 1] = {0}; // NESW edge current capacities: -1 == no edge
//     int32_t capacities[NUM_NEIGHBOURS + 1] = {0}; // NESW edge max capacities: -1 == no edge
// };

// struct terminal { // Source/Sink
//     uint32_t height = 0;
//     int32_t curr_capacities[NUM_NODES] = {0};
//     int32_t capacities[NUM_NODES] = {0}; // max capacities to each node: -1 == no edge
// };

// startNode = NUM_NODES+1
// endNode = NUM_NODES
// int breadthFirstSearch(node* nodeList, int* parentsList, terminal* source)
// {
//     int currentPathCapacity[NUM_NODES] = {0};
    
//     for(int i=0; i<NUM_NODES+1; i++){
//       parentsList[i] = -1;
//     }

//     // queue<int> q;
//     int q[NUM_NODES+3];
//     int qs=0, qe=0;

//     // Perform manual first push of BFS
//     for(int i=0; i<NUM_NODES; ++i){
//       if (source->capacities[i]>0) {
//         currentPathCapacity[i] = source->capacities[i];
//         parentsList[i] = NUM_NODES+1;
//         q[qe++] = i;
//       }
//     }


//     // while(!q.empty())
//     while(qs<qe)
//     {
//         #define min(a,b) ((a)<(b)?(a):(b))

//         int currentNode = q[qs++];

//         // Check if it can see sink
//         if (nodeList[currentNode].capacities[SINK]>0) {
//             parentsList[NUM_NODES] = currentNode;
//             return min(currentPathCapacity[currentNode], nodeList[currentNode].capacities[SINK]);
//         }

//         // Otherwise, try other edges
//         for (int i=0; i<NUM_NEIGHBOURS; ++i) {
//             int to = currentNode+DIFF[i];
//             if (nodeList[currentNode].capacities[i] > 0 && parentsList[to] == -1)
//             {
//                 parentsList[to] = currentNode;
//                 currentPathCapacity[to] = min(currentPathCapacity[currentNode], nodeList[currentNode].capacities[i]);
//                 q[qe++] = to;
//             }
//         }

//     }
    
//     return 0;
// }

// void edmondsKarp(node* nodeList, terminal* source, int32_t* flow, int8_t* cut)
// {
//     int maxFlow = 0;

//     int parentsList[NUM_NODES+2];

//     // Keep filling up all paths until maximum flow is reached
//     while(true)
//     {
//         int f = breadthFirstSearch(nodeList, parentsList, source);

//         // printf("flow: %d\n", flow);

//         if (f == 0)
//         {
//             break;
//         }

//         maxFlow += f;

//         // Perform sink stuff manually
//         int prev = parentsList[NUM_NODES]; // Parent of sink
//         nodeList[prev].capacities[SINK] -= f;

//         int curr = prev;
//         prev = parentsList[curr];
        
//         // Backtrack regularly
//         while(prev != NUM_NODES+1)
//         {
//             for (int i = 0; i < NUM_NEIGHBOURS; ++i) 
//             {
//                 if (curr - prev == DIFF[i])
//                 {
//                     nodeList[prev].capacities[i] -= f;
//                     nodeList[curr].capacities[i^0x2] += f;
//                 }
//             }
            
//             curr = prev;
//             prev = parentsList[curr];
//         }

//         // Perform source stuff manually
//         source->capacities[curr] -= f;
//     }

//     // printf("Foreground:\n");
//     for(int i=0; i<NUM_NODES; ++i)
//     {
//         cut[i] = parentsList[i] != -1;
//         // if (parentsList[i] != -1) {
//         //     // printf("%d\n", i);
//         //     cut[i] = 1;
//         // }
//     }

//     *flow = maxFlow;

// }

void edmondskarp(int32_t* capacities, int32_t* source_caps, int32_t* flow, int32_t* cut) {
    int maxFlow = 0;

    int parentsList[NUM_NODES+2];

    // Keep filling up all paths until maximum flow is reached
    while(1)
    {
        // Perform Breadth-First Search
        int f = 0;
        {
            int currentPathCapacity[NUM_NODES];
    
            #pragma clang loop unroll_count(NUM_NODES+1)
            for(int i=0; i<NUM_NODES+1; i++){
                parentsList[i] = -1;
            }

            int q[NUM_NODES+3];
            int qs=0, qe=0;

            // Perform manual first push of BFS
            // #pragma clang loop unroll_count(NUM_NODES)
            for(int i=0; i<NUM_NODES; ++i){
                if (source_caps[i]>0) {
                    currentPathCapacity[i] = source_caps[i];
                    parentsList[i] = NUM_NODES+1;
                    q[qe++] = i;
                }
            }

            // while(!q.empty())
            while(qs<qe)
            {
                #define min(a,b) ((a)<(b)?(a):(b))

                int currentNode = q[qs++];
                // printf("%03d : %03d \n", currentNode, currentPathCapacity[currentNode]);

                // Check if it can see sink
                if (capacities[(blk_sz*currentNode) + SINK]>0) {
                    parentsList[NUM_NODES] = currentNode;
                    f = min(currentPathCapacity[currentNode], capacities[(blk_sz*currentNode) + SINK]);
                    break;
                }

                // Otherwise, try other edges
                // #pragma clang loop unroll_count(NUM_NEIGHBOURS)
                for (int i=0; i<NUM_NEIGHBOURS; ++i) {
                    int to = currentNode+DIFF[i];
                    if (capacities[blk_sz*currentNode + i] > 0 && parentsList[to] == -1)
                    {
                        parentsList[to] = currentNode;
                        currentPathCapacity[to] = min(currentPathCapacity[currentNode], capacities[blk_sz*currentNode + i]);
                        q[qe++] = to;
                    }
                }
            }
        }
        
        // printf("flow: %d\n", flow);

        if (f == 0)
        {
            break;
        }

        maxFlow += f;

        // Perform sink stuff manually
        int prev = parentsList[NUM_NODES]; // Parent of sink
        capacities[blk_sz*prev + SINK] -= f;
        // nodes[prev].capacities[SINK] -= f;

        int curr = prev;
        prev = parentsList[curr];
        
        // Backtrack regularly
        // printf("Flow: %03d \n", f);
        while(prev != NUM_NODES+1)
        {
            // printf("%03d <- %03d\n", prev, curr);
            for (int i = 0; i < NUM_NEIGHBOURS; ++i) 
            {
                if (curr - prev == DIFF[i])
                {
                    capacities[blk_sz*prev + i] -= f;
                    capacities[blk_sz*curr + (i^0x2)] += f;
                    // nodes[prev].capacities[i] -= f;
                    // nodes[curr].capacities[i^0x2] += f;
                }
            }
            
            curr = prev;
            prev = parentsList[curr];
        }

        // Perform source stuff manually
        // source->capacities[curr] -= f;
        source_caps[curr] -= f;
    }

    // printf("Foreground:\n");
    for(int i=0; i<NUM_NODES; ++i)
    {
        cut[i] = (parentsList[i] != -1);
    }

    *flow = maxFlow;
}

int main(void) {
    TYPE* base = (TYPE*) 0x80100000;
    int64_t base2 = 0x80200000;
    
    // Input
    int32_t* capacities = (int32_t*) base2;
    uint64_t cap_size = 4 * NUM_NODES * (NUM_NEIGHBOURS+1);

    int32_t* source_caps = (int32_t*) (base2 + cap_size);

    // node* nodes = (node*) base2;
    // uint64_t nodes_size = sizeof(node) * NUM_NODES;

    // terminal* source = (terminal*) base2 + nodes_size;
    
    // Output
    int32_t* flow = (int32_t*) 0x80500000;
    int32_t* cut = (int32_t*) 0x80500004;// + sizeof(int32_t);

    for (int i = 0; i < 2*NUM_NODES; i++) {
        printf("%03d\n", base[i]);
    }

    int32_t pix_vals[NUM_NODES];
    // terminal source; // Source has no bi-directional (startpoint) // ai
    // terminal sink; // Sink has no bi-directional (endpoint) // bi = 255 - ai

    //============= Graph Creation =====================

    // Set pixels to input values
    for (int i = 0; i < NUM_NODES; i++) {
        pix_vals[i] = base[i] >> 2;
    }
    
    // Set source->node capacities (ai) 
    for (int i = 0; i < NUM_NODES; i++) {
        source_caps[i] = base[i+25];
    }
    
    // Set max capacities of each pixel's neighbours: 255 - |neighbour.pixel_value - curr.pixel_value|
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int i = (col + row*NUM_COLS);
            
            #define abs(a) ((a)<0?(-a):(a))

            // Check W neighbour
            if (col != 0) {
                // node w_neighbour = nodes[(col - 1) + row*NUM_COLS];
                // curr_node.capacities[WEST] = 63 - abs(curr_node.pixel_value - w_neighbour.pixel_value);
                capacities[blk_sz*i + WEST] = 63 - abs(pix_vals[i] - pix_vals[i + DIFF[WEST]]);
                // curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check N neighbour
            if (row != 0) {
                // node n_neighbour = nodes[col + (row - 1)*NUM_COLS];
                // curr_node.capacities[NORTH] = 63 - abs(curr_node.pixel_value - n_neighbour.pixel_value);
                capacities[blk_sz*i + NORTH] = 63 - abs(pix_vals[i] - pix_vals[i + DIFF[NORTH]]);
                // curr_node.curr_capacities[NORTH] = 0;
            }
            
            // Check E neighbour
            if (col != NUM_COLS - 1) {
                // node e_neighbour = nodes[(col + 1) + row*NUM_COLS];
                // curr_node.capacities[EAST] = 63 - abs(curr_node.pixel_value - e_neighbour.pixel_value);
                capacities[blk_sz*i + EAST] = 63 - abs(pix_vals[i] - pix_vals[i + DIFF[EAST]]);
                // curr_node.curr_capacities[EAST] = 0;
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                // node s_neighbour = nodes[col + (row + 1)*NUM_COLS];
                // curr_node.capacities[SOUTH] = 63 - abs(curr_node.pixel_value - s_neighbour.pixel_value);
                capacities[blk_sz*i + SOUTH] = 63 - abs(pix_vals[i] - pix_vals[i + DIFF[SOUTH]]);
                // curr_node.curr_capacities[SOUTH] = 0;
            }
            
            // Set capacity to sink (bi): 255 - ai
            capacities[blk_sz*i+SINK] = 255 - source_caps[i];
            // curr_node.capacities[SINK] = 255 - source->capacities[curr_node_i];
        }
    }

    m5_reset_stats();

    // Starts top
    // *top = 1;
    // while (*top != 0)
    // ;

    // Run Edmonds
    // edmondskarp(capacities, source_caps, flow, cut);
    // printf("f:%d\n", *flow);

    /* Run Accelerator */

    // Set arguments e.g.,
    
    // struct test* tes = (struct test*)0x80600000;
    // tes->a = 5;
    // tes->b = 5;
        

    *top = 0x0;
    *arg1 = (uint32_t)(void *) capacities;
    *arg2 = (uint32_t)(void *) source_caps;
    *arg3 = (uint32_t)(void *) flow;
    *arg4 = (uint32_t)(void *) cut;

    *top = 0x01;
    int count = 0;
    while (*top != 0)
        count++;
    printf("c:%03d\n", count);
    // printf("%d   \n", *pl); 

    for(int i=0; i<NUM_NODES; ++i) {
        printf("%03d %03d\n", cut[i], i);
    }
    printf("Flow: %03d\n", *flow);
    // printf("test: %d %d\n", tes->a, tes->b);
    printf("%03d\n", (int32_t)(cut - flow));

    m5_dump_stats();
    m5_exit();
}
