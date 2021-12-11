#include "../hw_defines.h"

void pushrelabel(
    uint64_t* heights, 
    uint32_t* excess_flows, 
    uint32_t* pixel_values,
    int32_t* nodes_curr_capacities,
    int32_t* nodes_capacities,
    int32_t* res_curr_capacities,
    uint32_t* source_height,
    uint32_t* source_excess_flow,
    int32_t* source_curr_capacities,
    int32_t* source_capacities,
    int32_t* sink_height,
    uint32_t* sink_excess_flow,
    int32_t* sink_curr_capacities,
    int32_t* sink_capacities,
    int32_t* res_source_curr_capacities)
{
   heights[0] = (uint64_t)heights;
   pixel_values[0] = 65;
}
