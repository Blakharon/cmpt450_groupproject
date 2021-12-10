//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "../defines.h"

#define DEV_INIT 0x01
#define DEV_INTR 0x04



// Device MMR addresses
#define TOP 0x2f000000
#define TOP_ARG1 0x2f000001
#define TOP_ARG2 0x2f000009
// Not required leaving it in here for future extensions
#define TOP_ARG3  0x2f000017
#define TOP_ARG4  0x2f000025
#define TOP_ARG5  0x2f000033
#define TOP_ARG6  0x2f000041
#define TOP_ARG7  0x2f000049
#define TOP_ARG8  0x2f000057
#define TOP_ARG9  0x2f000065
#define TOP_ARG10 0x2f000073
#define TOP_ARG11 0x2f000081
#define TOP_ARG12 0x2f000089
#define TOP_ARG13 0x2f000097
#define TOP_ARG14 0x2f000105
#define TOP_ARG15 0x2f000113

#define Pushrelabel       0x2f000200
#define Pushrelabel_ARG1  0x2f000201
#define Pushrelabel_ARG2  0x2f000209
#define Pushrelabel_ARG3  0x2f000217
#define Pushrelabel_ARG4  0x2f000225
#define Pushrelabel_ARG5  0x2f000233
#define Pushrelabel_ARG6  0x2f000241
#define Pushrelabel_ARG7  0x2f000249
#define Pushrelabel_ARG8  0x2f000257
#define Pushrelabel_ARG9  0x2f000265
#define Pushrelabel_ARG10 0x2f000273
#define Pushrelabel_ARG11 0x2f000281
#define Pushrelabel_ARG12 0x2f000289
#define Pushrelabel_ARG13 0x2f000297
#define Pushrelabel_ARG14 0x2f000305
#define Pushrelabel_ARG15 0x2f000313
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
