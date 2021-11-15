#include "../hw_defines.h"

void top(uint64_t m1_addr, uint64_t m2_addr, uint64_t SIZE) {
  // Define Device MMRs
  volatile uint8_t *ArgmaxFlag = (uint8_t *)Argmax;
  volatile uint64_t *ArgmaxArg1 = (uint64_t *)(Argmax + 1);
  volatile uint64_t *ArgmaxArg2 = (uint64_t *)(Argmax + 9);
  volatile uint64_t *ArgmaxArg3 = (uint64_t *)(Argmax + 17);

  *ArgmaxFlag = 0x0;

  //   // DMA Data into accelerator
  volatile uint8_t *DmaFlags = (uint8_t *)(DMA);
  volatile uint64_t *DmaRdAddr = (uint64_t *)(DMA + 1);
  volatile uint64_t *DmaWrAddr = (uint64_t *)(DMA + 9);
  volatile uint32_t *DmaCopyLen = (uint32_t *)(DMA + 17);

  // Defining range of address in scratchpad for input and output.
  uint64_t SCRATCHPAD_INPUT = ArgmaxSPM;
  uint64_t SCRATCHPAD_OUTPUT = ArgmaxSPM + 0x24;

  // DRAM to SCRATCHPAD
  *DmaRdAddr = m1_addr;
  *DmaWrAddr = ArgmaxSPM;
  // Bytes to be copied into bytes
  *DmaCopyLen = 0x24;
  *DmaFlags = DEV_INIT;
  //   // Poll DMA for finish
  while ((*DmaFlags & DEV_INTR) != DEV_INTR)
    ;

  // Set up arguments for accelerator.
  *ArgmaxArg1 = SCRATCHPAD_INPUT;
  *ArgmaxArg2 = SCRATCHPAD_OUTPUT;
  *ArgmaxArg3 = SIZE;


  while (*ArgmaxFlag != 0x0)
    ;
  // Start the accelerated function
  *ArgmaxFlag = DEV_INIT;
  //  Poll function for finish
  while ((*ArgmaxFlag & DEV_INTR) != DEV_INTR)
    ;
  *ArgmaxFlag = 0x0;

  *DmaRdAddr = SCRATCHPAD_OUTPUT;
  *DmaWrAddr = m2_addr;
  *DmaCopyLen = sizeof(TYPE); // Number of bytes to copy back.
  *DmaFlags = DEV_INIT;
  // Poll DMA for finish
  while ((*DmaFlags & DEV_INTR) != DEV_INTR)
    ;

  return;
}