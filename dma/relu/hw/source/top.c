#include "../hw_defines.h"

void top(uint64_t m1_addr, uint64_t m2_addr, uint64_t SIZE) {
  // Define Device MMRs
  volatile uint8_t *ReluFlag = (uint8_t *)Relu;
  volatile uint64_t *ReluArg1 = (uint64_t *)(Relu + 1);
  volatile uint64_t *ReluArg2 = (uint64_t *)(Relu + 9);
  volatile uint64_t *ReluArg3 = (uint64_t *)(Relu + 17);

  *ReluFlag = 0x0;

//   // DMA Data into accelerator
  volatile uint8_t *DmaFlags = (uint8_t *)(DMA);
  volatile uint64_t *DmaRdAddr = (uint64_t *)(DMA + 1);
  volatile uint64_t *DmaWrAddr = (uint64_t *)(DMA + 9);
  volatile uint32_t *DmaCopyLen = (uint32_t *)(DMA + 17);


  // Defining range of address in scratchpad for input and output.
  uint64_t SCRATCHPAD_INPUT = ReluSPM;
  uint64_t SCRATCHPAD_OUTPUT = ReluSPM + sizeof(TYPE)*SIZE;

  // DRAM to SCRATCHPAD
  *DmaRdAddr = m1_addr;
  *DmaWrAddr = ReluSPM;
  // Bytes to be copied into bytes
  *DmaCopyLen = 0x24;
  *DmaFlags = DEV_INIT;
//   // Poll DMA for finish
  while ((*DmaFlags & DEV_INTR) != DEV_INTR)
    ;

  // Set up arguments for accelerator.
  *ReluArg1 = SCRATCHPAD_INPUT;
  *ReluArg2 = SCRATCHPAD_OUTPUT;
  *ReluArg3 = SIZE;
  while(*ReluFlag != 0x0);

  // //   // // Start the accelerated function
  *ReluFlag = DEV_INIT;

// //   // // Poll function for finish
  while ((*ReluFlag & DEV_INTR) != DEV_INTR);
  *ReluFlag = 0x0;

  *DmaRdAddr = SCRATCHPAD_OUTPUT;
  *DmaWrAddr = m2_addr;
  *DmaCopyLen = 0x24;
  *DmaFlags = DEV_INIT;
  // Poll DMA for finish
  while ((*DmaFlags & DEV_INTR) != DEV_INTR)
    ;

  return;
}