#ifndef __DEFINES_H__
#define __DEFINES_H__

#define CHECK

#define TYPE int32_t
#define TYPE_PTR int32_t*

#define N 4

#define NUM_NEIGHBOURS 4

#define NUM_NODES 225
#define NUM_ROWS 15
#define NUM_COLS 15

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define SINK 4

const int32_t DIFF[] = {-NUM_COLS, 1, NUM_COLS, -1};
const int32_t blk_sz = NUM_NEIGHBOURS+1;

// struct node { // Pixel
//     uint32_t height;
//     uint32_t pixel_value;
//     int32_t curr_capacities[NUM_NEIGHBOURS + 1]; // NESW edge current capacities: -1 == no edge
//     int32_t capacities[NUM_NEIGHBOURS + 1]; // NESW edge max capacities: -1 == no edge
// };

// struct terminal { // Source/Sink
//     uint32_t height;
//     int32_t curr_capacities[NUM_NODES];
//     int32_t capacities[NUM_NODES]; // max capacities to each node: -1 == no edge
// };

// struct test {
//     int32_t a;
//     int32_t b;
// };

#endif
