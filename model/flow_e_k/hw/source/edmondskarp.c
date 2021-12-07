#include "../hw_defines.h"

void edmondskarp(struct node* nodes, struct terminal* source, int32_t* flow, int32_t* cut) {
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
                if (source->capacities[i]>0) {
                    currentPathCapacity[i] = source->capacities[i];
                    parentsList[i] = NUM_NODES+1;
                    q[qe++] = i;
                }
            }

            // while(!q.empty())
            *flow = 0;
            for(int i=0; i<NUM_NODES; ++i){
                flow[i] = source->capacities[i] + 31;
            }
            *flow = (int) source;
            return;
            while(qs<qe)
            {
                #define min(a,b) ((a)<(b)?(a):(b))

                int currentNode = q[qs++];

                *flow = nodes[currentNode].capacities[SINK];
                *flow = 1/(5^2-5^2);
                return;

                // Check if it can see sink
                if (nodes[currentNode].capacities[SINK]>0) {
                    parentsList[NUM_NODES] = currentNode;
                    f = min(currentPathCapacity[currentNode], nodes[currentNode].capacities[SINK]);
                    break;
                }

                // Otherwise, try other edges
                // #pragma clang loop unroll_count(NUM_NEIGHBOURS)
                for (int i=0; i<NUM_NEIGHBOURS; ++i) {
                    int to = currentNode+DIFF[i];
                    if (nodes[currentNode].capacities[i] > 0 && parentsList[to] == -1)
                    {
                        parentsList[to] = currentNode;
                        currentPathCapacity[to] = min(currentPathCapacity[currentNode], nodes[currentNode].capacities[i]);
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
        nodes[prev].capacities[SINK] -= f;

        int curr = prev;
        prev = parentsList[curr];
        
        // Backtrack regularly
        while(prev != NUM_NODES+1)
        {
            for (int i = 0; i < NUM_NEIGHBOURS; ++i) 
            {
                if (curr - prev == DIFF[i])
                {
                    nodes[prev].capacities[i] -= f;
                    nodes[curr].capacities[i^0x2] += f;
                }
            }
            
            curr = prev;
            prev = parentsList[curr];
        }

        // Perform source stuff manually
        source->capacities[curr] -= f;
    }

    // printf("Foreground:\n");
    for(int i=0; i<NUM_NODES; ++i)
    {
        // cut[i] = (parentsList[i] != -1);
        // cut[i] = 1;

        // if (parentsList[i] != -1) {
        //     // printf("%d\n", i);
        //     cut[i] = 1;
        // }
    }

    *flow = maxFlow;
}