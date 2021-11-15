#include "../hw_defines.h"

void argmax(TYPE m1[N], TYPE_PTR m2, TYPE SIZE) {
 *m2 = 0;
#pragma clang unroll_count(1)
  for (int i = 0; i < SIZE; i++) {
    if (m1[i] > m1[*m2]) {
      *m2 = i;
    }
  }
}
