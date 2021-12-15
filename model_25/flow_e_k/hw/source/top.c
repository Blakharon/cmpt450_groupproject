#include "../hw_defines.h"

void top(uint64_t capacities, uint64_t source_caps, uint64_t flow, uint64_t cut) {
  // Define Device MMRs
  volatile uint8_t *EdmondsKarpFlag = (uint8_t *)EdmondsKarp;
  volatile uint64_t *EdmondsKarpArg1 = (uint64_t *)(EdmondsKarp_ARG1);
  volatile uint64_t *EdmondsKarpArg2 = (uint64_t *)(EdmondsKarp_ARG2);
  volatile uint64_t *EdmondsKarpArg3 = (uint64_t *)(EdmondsKarp_ARG3);
  volatile uint64_t *EdmondsKarpArg4 = (uint64_t *)(EdmondsKarp_ARG4);

  *EdmondsKarpFlag = 0x0;
  // Set up arguments for accelerator.

  *EdmondsKarpArg1 = capacities;
  *EdmondsKarpArg2 = source_caps;
  *EdmondsKarpArg3 = flow;
  *EdmondsKarpArg4 = cut;
  // Start the accelerated function
  *EdmondsKarpFlag = DEV_INIT;

  // Poll function for finish
  while ((*EdmondsKarpFlag & DEV_INTR) != DEV_INTR)
    ;
  *EdmondsKarpFlag = 0x0;

  return;
}
