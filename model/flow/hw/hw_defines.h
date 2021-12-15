//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "../defines.h"

#define DEV_INIT 0x01
#define DEV_INTR 0x04



// Device MMR addresses
#define TOP       0x2f000000
#define TOP_ARG1  0x2f000001
#define TOP_ARG2  0x2f000009
// Not required leaving it in here for future extensions
#define TOP_ARG3  0x2f000011
#define TOP_ARG4  0x2f000019
#define TOP_ARG5  0x2f000021
#define TOP_ARG6  0x2f000029
#define TOP_ARG7  0x2f000031
#define TOP_ARG8  0x2f000039
#define TOP_ARG9  0x2f000041
#define TOP_ARG10 0x2f000049
#define TOP_ARG11 0x2f000051
#define TOP_ARG12 0x2f000059
#define TOP_ARG13 0x2f000061
#define TOP_ARG14 0x2f000069
#define TOP_ARG15 0x2f000071

#define Pushrelabel       0x2f000200
#define Pushrelabel_ARG1  0x2f000201
#define Pushrelabel_ARG2  0x2f000209
#define Pushrelabel_ARG3  0x2f000211
#define Pushrelabel_ARG4  0x2f000219
#define Pushrelabel_ARG5  0x2f000221
#define Pushrelabel_ARG6  0x2f000229
#define Pushrelabel_ARG7  0x2f000231
#define Pushrelabel_ARG8  0x2f000239
#define Pushrelabel_ARG9  0x2f000241
#define Pushrelabel_ARG10 0x2f000249
#define Pushrelabel_ARG11 0x2f000251
#define Pushrelabel_ARG12 0x2f000259
// Not required leaving it in here for future extensions


// TODO: CHECK THE ADDRESSES HERE ARE WHERE YOU WANT THEM TO BE FOR PERFORMING
// THE COMPUTATION This is not useful for the cache implementations. Specify
// row/column sizes Specify the scratchpad base address
#define DMA 0x2ff00000

#define ArgmaxSPM 0x2f200000
#define vector_size N * sizeof(TYPE)
// Specify offsets where Argmax inputs and outputs are going to be stored in the
// scratchpad
#define ArgmaxM1 SPM + (vector_size * 0)
#define ArgmaxM2 SPM + (vector_size * 1)
