#include "../hw_defines.h"

#define hello(a) 42

void pushrelabel(TYPE_PTR SIZE) {
    //int hello2 = hello();
    *SIZE = hello(12);
}
