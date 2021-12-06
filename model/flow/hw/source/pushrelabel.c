#include "../hw_defines.h"

int hello() {
    return 42;
}

void pushrelabel(TYPE_PTR SIZE) {
    &SIZE = hello();
}
