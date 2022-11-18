#include <assert.h>
#include "calc.h"

int main() {
  push(1000.0);
  push(1001.0);
  assert(pop() == 1001.0);
  push(1002.0);
  assert(pop() == 1002.0);
  assert(pop() == 1000.0);

  assert(pop() == 0.0);

  for (int i = 0; i < 103; i++) {
    push(i);
  }
  assert(pop() == 99.0);
  assert(pop() == 98.0);
}