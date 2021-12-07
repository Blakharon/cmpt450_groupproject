#include "../hw_defines.h"

#define hello(a) 42

void pushrelabel(teststruct *SIZE) {
    //int hello2 = hello();
   SIZE->a = 42;
   SIZE->b = 30;
}
