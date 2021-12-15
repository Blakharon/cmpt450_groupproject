#include "../hw_defines.h"

void edmondskarp(int32_t* capacities, int32_t* source_caps, int32_t* flow, int32_t* cut) {
    int32_t maxFlow = 0;

    volatile int32_t* parentsList = (int32_t*) 0x80600000;
    volatile int32_t* currentPathCapacity = (int32_t*) (0x80600000 + (NUM_NODES+2)*sizeof(int32_t));
    volatile int32_t* q = (int32_t*) (0x80600000 + (NUM_NODES+2)*sizeof(int32_t) + (NUM_NODES+2)*sizeof(int32_t));
    int32_t f;

    // flow[10] = (int32_t) capacities[blk_sz*12];

    // return;

    // for(int32_t i = 0; i<NUM_NODES; ++i){
    //     cut[i] = capacities[blk_sz*i + NORTH];
    // }

    // int tmp = 0;
    // for(int i = 0; i<NUM_NODES*blk_sz; ++i){
    //     tmp += capacities[i];
    // }

    // *flow = tmp;

    // return;
    // int32_t iii = 0;

    // Keep filling up all paths until maximum flow is reached
    while(1)
    {
        // Perform Breadth-First Search
        f = 0;
        
        #pragma clang loop unroll_count(NUM_NODES+1)
        for(int32_t i=0; i<NUM_NODES+1; i++){
            parentsList[i] = -1;
        }

        int32_t qs=0, qe=0; // Queue start and end

        // Perform manual first push of BFS
        // Tested, can't unroll this without breaking
        for(int32_t i=0; i<NUM_NODES; ++i){
            if (source_caps[i]>0) {
                currentPathCapacity[i] = source_caps[i];
                parentsList[i] = NUM_NODES+1;
                q[qe++] = i;
            }
        }

        // While the queue isn't empty
        while(qs<qe)
        {
            #define min(a,b) ((a)<(b)?(a):(b))

            int32_t currentNode = q[qs++];

            // Check if it can see sink
            if (capacities[(blk_sz*currentNode) + SINK]>0) {
                parentsList[NUM_NODES] = currentNode;
                f = min(currentPathCapacity[currentNode], capacities[(blk_sz*currentNode) + SINK]);
                break;
            }

            // Otherwise, try other edges
            #pragma clang loop unroll_count(NUM_NEIGHBOURS)
            for (int32_t i=0; i<NUM_NEIGHBOURS; ++i) {
                int to = currentNode+DIFF[i];
                if (capacities[blk_sz*currentNode + i] > 0 && parentsList[to] == -1)
                {
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode], capacities[blk_sz*currentNode + i]);
                    q[qe++] = to;
                }
            }
        }
        
        if (f == 0)
        {
            break;
        }

        maxFlow += f;

        // Perform sink flow manually
        int32_t prev = parentsList[NUM_NODES]; // Parent of sink        
        capacities[blk_sz*prev + SINK] -= f;

        volatile int32_t curr = prev;
        prev = parentsList[curr];
        
        // Backtrack linearly
        while(prev != NUM_NODES+1)
        {
            #pragma clang loop unroll_count(NUM_NEIGHBOURS)
            for (int32_t i = 0; i < NUM_NEIGHBOURS; ++i) 
            {
                if (curr - prev == DIFF[i])
                {
                    capacities[blk_sz*prev + i] -= f;
                    capacities[blk_sz*curr + (i^0x2)] += f;
                }
            }
            curr = prev;
            prev = parentsList[curr];
        }

        // Perform source flow adjustment manually
        source_caps[curr] -= f;
    }

    // Set foreground and background nodes
    for(int32_t i=0; i<NUM_NODES; ++i)
    {
        cut[i] = (parentsList[i] != -1);
    }

    // Set output flow
    *flow = maxFlow;
}