#ifndef __DEFINES_H__
#define __DEFINES_H__

#define CHECK

#define TYPE int32_t
#define TYPE_PTR int32_t*

#define NUM_NEIGHBOURS 4

#define NUM_NODES 25
#define NUM_ROWS 5
#define NUM_COLS 5

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define SINK 4

struct __attribute__((__packed__)) pixel {
    uint32_t height;
    uint32_t excess_flow;
    uint32_t pixel_value;
    int32_t curr_capacities[NUM_NEIGHBOURS + 1]; // NESW edge current capacities: -1 == no edge
    int32_t capacities[NUM_NEIGHBOURS + 1]; // NESW edge max capacities: -1 == no edge
};

struct __attribute__((__packed__)) terminal { // Source/Sink
    uint32_t height;
    uint32_t excess_flow;
    int32_t curr_capacities[NUM_NODES];
    int32_t capacities[NUM_NODES]; // max capacities to each node: -1 == no edge
};

struct __attribute__((__packed__)) teststruct {
    uint64_t a;
    uint64_t b;
};

#endif
