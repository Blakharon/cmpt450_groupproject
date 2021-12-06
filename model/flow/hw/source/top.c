#include "../hw_defines.h"

void top(uint64_t m1_addr, uint64_t m2_addr, uint64_t SIZE) {
  // Define Device MMRs
  volatile uint8_t *ArgmaxFlag = (uint8_t *)Argmax;
  volatile uint64_t *ArgmaxArg1 = (uint64_t *)(Argmax_ARG1);
  volatile uint64_t *ArgmaxArg2 = (uint64_t *)(Argmax_ARG2);
  volatile uint64_t *ArgmaxArg3 = (uint64_t *)(Argmax_ARG3);

  *ArgmaxFlag = 0x0;
  // // Set up arguments for accelerator.

  *ArgmaxArg1 = m1_addr;
  *ArgmaxArg2 = m2_addr;
  *ArgmaxArg3 = SIZE;
  // // Start the accelerated function
  *ArgmaxFlag = DEV_INIT;

  // // Poll function for finish
  while ((*ArgmaxFlag & DEV_INTR) != DEV_INTR)
    ;
  *ArgmaxFlag = 0x0;

  return;
}
