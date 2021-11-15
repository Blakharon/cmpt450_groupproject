#include "../../common/m5ops.h"
#include "../defines.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
                                      
volatile uint8_t *top =    (uint8_t *)0x2f000000;
volatile uint32_t *arg1 = (uint32_t *)0x2f000001;
volatile uint32_t *arg2 = (uint32_t *)0x2f000009;
volatile uint32_t *arg3 = (uint32_t *)0x2f000011;
volatile uint32_t *arg4 = (uint32_t *)0x2f000019;
volatile uint32_t *arg5 = (uint32_t *)0x2f000021;
volatile uint32_t *arg6 = (uint32_t *)0x2f000029;
volatile uint32_t *arg7 = (uint32_t *)0x2f000031;
volatile uint32_t *arg8 = (uint32_t *)0x2f000039;

int main(void) {
  printf("Hello World \n");
 

  m5_reset_stats();
  // bool fail = false;
  // // stage = 0;
  TYPE array[9] = {1, -2, 3, -4, 5, -6, 7, -8, 9};
  TYPE base = 0x80100000;
              
      // Move local stack to global array
      for (int i = 0; i < 9; i++) {
    *((TYPE *)base + i) = array[i];

  }

  TYPE *m1 = (TYPE *)base;
  TYPE *m2 = (TYPE *)(base + sizeof(TYPE) * 16);
  TYPE *m3 = (TYPE *)(base + 2 * sizeof(TYPE) * 16);

  for (int i = 0; i < N; i++) {
    printf("%d \n", m1[i]);  
  }

  // Set arguments e.g.,
  *top = 0x0;
  *arg1 = (uint32_t)(void *)m1;
  *arg2 = (uint32_t)(void *)m2;
  *arg3 = N;
  // // // Dummy to check if they are being written
  // *arg3 = (uint32_t)(void *)m2;
  // *arg4 = (uint32_t)(void *)m2;
  // *arg5 = (uint32_t)(void *)m2;
  // *arg6 = (uint32_t)(void *)m2;
  // *arg7 = (uint32_t)(void *)m2;
  // *arg8 = (uint32_t)(void *)m2;

  // TODO: Start top
  *top = 1;
  unsigned *common_val = (unsigned*)0x8f000000;
  while (*top != 0);


   for (int i = 0; i < N; i++) {
     printf("%d \n", m2[i]);
    }

  //   // TODO: Check if top is done.

  //   // TODO: Check result

  //  #ifdef CHECK
  //   if (fail)
  //     printf("Check Failed\n");
  //   else
  //     printf("Check Passed\n");
  // #endif
    m5_dump_stats();
    m5_exit();
}
