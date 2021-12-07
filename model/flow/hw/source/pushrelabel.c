#include "../hw_defines.h"

#define hello(a) 42

void pushrelabel(struct teststruct *SIZE) {
    //int hello2 = hello();
   SIZE->a = (uint64_t)(&(SIZE->b));
   SIZE->b = 30;
}
