#include "../hw_defines.h"

void top(uint64_t pl_arg1) {
  // Define Device MMRs
  volatile uint8_t *PushrelabelFlag = (uint8_t *)Pushrelabel;
  volatile uint64_t *PushrelabelArg1 = (uint64_t *)(Pushrelabel_ARG1);
  volatile uint64_t *PushrelabelArg2 = (uint64_t *)(Pushrelabel_ARG2);
  volatile uint64_t *PushrelabelArg3 = (uint64_t *)(Pushrelabel_ARG3);

  *PushrelabelFlag = 0x0;
  // // Set up arguments for accelerator.

  *PushrelabelArg1 = pl_arg1;
  // // Start the accelerated function
  *PushrelabelFlag = DEV_INIT;

  // // Poll function for finish
  while ((*PushrelabelFlag & DEV_INTR) != DEV_INTR)
    ;
  *PushrelabelFlag = 0x0;

  return;
}
