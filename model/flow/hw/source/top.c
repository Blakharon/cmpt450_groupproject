#include "../hw_defines.h"

void top(
    uint64_t heights, 
    uint64_t excess_flows,  
    uint64_t nodes_curr_capacities, 
    uint64_t nodes_capacities, 
    uint64_t res_curr_capacities, 
    uint64_t source_height, 
    uint64_t source_excess_flow, 
    uint64_t source_curr_capacities, 
    uint64_t source_capacities, 
    uint64_t sink_height, 
    uint64_t sink_excess_flow, 
    uint64_t res_source_curr_capacities)
{
  // Define Device MMRs
  volatile uint8_t *PushrelabelFlag = (uint8_t *)Pushrelabel;
  volatile uint64_t *PushrelabelArg1  = (uint64_t *)(Pushrelabel_ARG1);
  volatile uint64_t *PushrelabelArg2  = (uint64_t *)(Pushrelabel_ARG2);
  volatile uint64_t *PushrelabelArg3  = (uint64_t *)(Pushrelabel_ARG3);
  volatile uint64_t *PushrelabelArg4  = (uint64_t *)(Pushrelabel_ARG4);
  volatile uint64_t *PushrelabelArg5  = (uint64_t *)(Pushrelabel_ARG5);
  volatile uint64_t *PushrelabelArg6  = (uint64_t *)(Pushrelabel_ARG6);
  volatile uint64_t *PushrelabelArg7  = (uint64_t *)(Pushrelabel_ARG7);
  volatile uint64_t *PushrelabelArg8  = (uint64_t *)(Pushrelabel_ARG8);
  volatile uint64_t *PushrelabelArg9  = (uint64_t *)(Pushrelabel_ARG9);
  volatile uint64_t *PushrelabelArg10 = (uint64_t *)(Pushrelabel_ARG10);
  volatile uint64_t *PushrelabelArg11 = (uint64_t *)(Pushrelabel_ARG11);
  volatile uint64_t *PushrelabelArg12 = (uint64_t *)(Pushrelabel_ARG12);

  *PushrelabelFlag = 0x0;
  // Set up arguments for accelerator.

  *PushrelabelArg1  = heights;
  *PushrelabelArg2  = excess_flows;
  *PushrelabelArg3  = nodes_curr_capacities;
  *PushrelabelArg4  = nodes_capacities;
  *PushrelabelArg5  = res_curr_capacities;
  *PushrelabelArg6  = source_height;
  *PushrelabelArg7  = source_excess_flow;
  *PushrelabelArg8  = source_curr_capacities;
  *PushrelabelArg9  = source_capacities;
  *PushrelabelArg10 = sink_height;
  *PushrelabelArg11 = sink_excess_flow;
  *PushrelabelArg12 = res_source_curr_capacities;
  
  // Start the accelerated function
  *PushrelabelFlag = DEV_INIT;

  // Poll function for finish
  while ((*PushrelabelFlag & DEV_INTR) != DEV_INTR)
    ;
  *PushrelabelFlag = 0x0;

  return;
}
