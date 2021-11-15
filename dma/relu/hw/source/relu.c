#include "../hw_defines.h"

void relu(TYPE m1[N], TYPE m2[N], TYPE SIZE) {
#pragma clang unroll_count(9)
  for (int i = 0; i < 9; i++) {
    if (m1[i] >= 0) {
      m2[i] = m1[i];
    } else {
      m2[i] = 0;
    }
  }
  return;
}
