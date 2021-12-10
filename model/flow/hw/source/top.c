#include "../hw_defines.h"

void top(
    uint64_t heights, 
    uint64_t excess_flows, 
    uint64_t pixel_values, 
    uint64_t nodes_curr_capacities, 
    uint64_t nodes_capacities, 
    uint64_t res_curr_capacities, 
    uint64_t source_height, 
    uint64_t source_excess_flow, 
    uint64_t source_curr_capacities, 
    uint64_t source_capacities, 
    uint64_t sink_height, 
    uint64_t sink_excess_flow, 
    uint64_t sink_curr_capacities, 
    uint64_t sink_capacities, 
    uint64_t res_source_curr_capacities)
{
  // Define Device MMRs
  volatile uint8_t *PushrelabelFlag = (uint8_t *)Pushrelabel;
  volatile uint64_t *PushrelabelArg1 = (uint64_t *)(Pushrelabel_ARG1);

  *PushrelabelFlag = 0x0;
  // Set up arguments for accelerator.

  *PushrelabelArg1 = heights;
  
  // Start the accelerated function
  *PushrelabelFlag = DEV_INIT;

  // Poll function for finish
  while ((*PushrelabelFlag & DEV_INTR) != DEV_INTR)
    ;
  *PushrelabelFlag = 0x0;

  return;
}
