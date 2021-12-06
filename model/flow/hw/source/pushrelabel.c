#include "../hw_defines.h"

inline int hello() {
    return 42;
}

void pushrelabel(TYPE_PTR SIZE) {
    //int hello2 = hello();
    *SIZE = hello();
}
