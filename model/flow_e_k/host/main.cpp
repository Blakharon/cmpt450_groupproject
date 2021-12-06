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

struct node { // Pixel
    uint32_t height = 0;
    uint32_t pixel_value;
    int32_t curr_capacities[NUM_NEIGHBOURS + 1] = {0}; // NESW edge current capacities: -1 == no edge
    int32_t capacities[NUM_NEIGHBOURS + 1] = {0}; // NESW edge max capacities: -1 == no edge
};

struct terminal { // Source/Sink
    uint32_t height = 0;
    int32_t curr_capacities[NUM_NODES] = {0};
    int32_t capacities[NUM_NODES] = {0}; // max capacities to each node: -1 == no edge
};

// startNode = NUM_NODES+1
// endNode = NUM_NODES
int breadthFirstSearch(node* nodeList, int* parentsList, terminal* source)
{
    int currentPathCapacity[NUM_NODES] = {0};
    
    for(int i=0; i<NUM_NODES+1; i++){
      parentsList[i] = -1;
    }

    // queue<int> q;
    int q[NUM_NODES+3];
    int qs=0, qe=0;

    // Perform manual first push of BFS
    for(int i=0; i<NUM_NODES; ++i){
      if (source->capacities[i]>0) {
        currentPathCapacity[i] = source->capacities[i];
        parentsList[i] = NUM_NODES+1;
        q[qe++] = i;
      }
    }


    // while(!q.empty())
    while(qs<qe)
    {
        #define min(a,b) ((a)<(b)?(a):(b))

        int currentNode = q[qs++];

        // Check if it can see sink
        if (nodeList[currentNode].capacities[SINK]>0) {
            parentsList[NUM_NODES] = currentNode;
            return min(currentPathCapacity[currentNode], nodeList[currentNode].capacities[SINK]);
        }

        // Otherwise, try other edges
        for (int i=0; i<NUM_NEIGHBOURS; ++i) {
            int to = currentNode+DIFF[i];
            if (nodeList[currentNode].capacities[i] > 0 && parentsList[to] == -1)
            {
                parentsList[to] = currentNode;
                currentPathCapacity[to] = min(currentPathCapacity[currentNode], nodeList[currentNode].capacities[i]);
                q[qe++] = to;
            }
        }

    }
    
    return 0;
}

int edmondsKarp(node* nodeList, terminal* source)
{
    int maxFlow = 0;

    int parentsList[NUM_NODES+2];

    // Keep filling up all paths until maximum flow is reached
    while(true)
    {
        int flow = breadthFirstSearch(nodeList, parentsList, source);

        // printf("flow: %d\n", flow);

        if (flow == 0)
        {
            break;
        }

        maxFlow += flow;

        // Perform sink stuff manually
        int prev = parentsList[NUM_NODES]; // Parent of sink
        nodeList[prev].capacities[SINK] -= flow;

        int curr = prev;
        prev = parentsList[curr];
        
        // Backtrack regularly
        while(prev != NUM_NODES+1)
        {
            for (int i = 0; i < NUM_NEIGHBOURS; ++i) 
            {
                if (curr - prev == DIFF[i])
                {
                    nodeList[prev].capacities[i] -= flow;
                    nodeList[curr].capacities[i^0x2] += flow;
                }
            }
            
            curr = prev;
            prev = parentsList[curr];
        }

        // Perform source stuff manually
        source->capacities[curr] -= flow;
    }

    printf("Foreground:\n");
    for(int i=0; i<NUM_NODES; ++i)
    {
        if (parentsList[i] != -1) {
            printf("%d\n", i);
        }
    }

    return maxFlow;
}

int main(void) {
    TYPE* base = (TYPE*) 0x80100000;

    for (int i = 0; i < 50; i++) {
        printf("%d   \n", base[i]);
    }

    node nodes[NUM_NODES];
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
            node& curr_node = nodes[curr_node_i];
            
            #define abs(a) ((a)<0?(-a):(a))

            // Check W neighbour
            if (col != 0) {
                node w_neighbour = nodes[(col - 1) + row*NUM_COLS];
                curr_node.capacities[WEST] = 63 - abs(curr_node.pixel_value - w_neighbour.pixel_value);
                curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check N neighbour
            if (row != 0) {
                node n_neighbour = nodes[col + (row - 1)*NUM_COLS];
                curr_node.capacities[NORTH] = 63 - abs(curr_node.pixel_value - n_neighbour.pixel_value);
                curr_node.curr_capacities[NORTH] = 0;
            }
            
            // Check E neighbour
            if (col != NUM_COLS - 1) {
                node e_neighbour = nodes[(col + 1) + row*NUM_COLS];
                curr_node.capacities[EAST] = 63 - abs(curr_node.pixel_value - e_neighbour.pixel_value);
                curr_node.curr_capacities[WEST] = 0;
            }
            
            // Check S neighbour
            if (row != NUM_ROWS - 1) {
                node s_neighbour = nodes[col + (row + 1)*NUM_COLS];
                curr_node.capacities[SOUTH] = 63 - abs(curr_node.pixel_value - s_neighbour.pixel_value);
            }
            
            // Set capacity to sink (bi): 255 - ai
            curr_node.capacities[SINK] = 255 - source.capacities[curr_node_i];
        }
    }

    m5_reset_stats();

    // Starts top
    // *top = 1;
    // while (*top != 0)
    // ;

    // Run Edmonds
    int f = edmondsKarp(nodes, &source);
    printf("Flow: %d\n", f);

    m5_dump_stats();
    m5_exit();
}
