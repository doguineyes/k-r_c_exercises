/*
  In a two's complement number system, x &= (x-1) deletes the rightmost 1 bit in x.
  Explain why. Use this observation to write a faster version of bitcount.
*/
#include <assert.h>

int bitcount(unsigned x) {
  int b = 0;
  while(x != 0) {
    x &= (x-1);
    b++;
  }
  return b;
}

int bitcount_ans(unsigned x) {
  int b;
  for (b = 0; x != 0; x >>= 1) {
    if (x & 01)
      b++;
  }
  return b;
}

int main() {
  assert(bitcount(1) == 1);
  assert(bitcount(0) == 0);
  assert(bitcount(2) == 1);
  assert(bitcount(5) == 2);
  assert(bitcount(7) == 3);
  assert(bitcount(8) == 1);

  int x1 = 218032241;
  assert(bitcount(x1) == bitcount_ans(x1));
}