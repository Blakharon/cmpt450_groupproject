#include "../hw_defines.h"

void edmondskarp(int32_t* capacities, int32_t* source_caps, int32_t* flow, int32_t* cut) {
    int maxFlow = 0;

    int parentsList[NUM_NODES+2];

    // flow[10] = (int32_t) capacities[blk_sz*12];

    // for(int i = 0; i<NUM_NODES; ++i){
    //     cut[i] = capacities[blk_sz*i + NORTH];
    // }

    // int tmp = 0;
    // for(int i = 0; i<NUM_NODES*blk_sz; ++i){
    //     tmp += capacities[i];
    // }

    // *flow = tmp;

    // return;
    int iii = 0;

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
            // pragma clang loop unroll_count(NUM_NODES)
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
        cut[iii++] = f;

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

    *flow = maxFlow;

    return;

    // printf("Foreground:\n");
    for(int i=0; i<NUM_NODES; ++i)
    {
        cut[i] = (parentsList[i] != -1);
    }

    *flow = maxFlow;
}