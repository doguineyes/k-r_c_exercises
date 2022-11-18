/*
  Write a function rightrot(x ,n) that returns the value of the integer
  x rotated to the right by n bit positions.
*/
#include <stdio.h>
#include <assert.h>

int getIntBits() {
  return sizeof(unsigned) * 8;
}

int rightrot(unsigned x, int n) {
  const int INT_BITS = getIntBits(); // 32
  if (n < 0) {
    return x;
  }
  int m = n % INT_BITS; // 0 <= m < 32
  if (m == 0) {
    return x;
  }
  int part1 = (x >> m);
  int part2 = (x << (INT_BITS - m));
  int result = part1 | part2;
  // printf("m=%d, part1=%x, part2=%x, result=%x\n", m, part1, part2, result);
  return result;
}

/* wordlength: computes word length of the machine */
int wordlength(void) {
  int i;
  unsigned v = (unsigned) ~0;
  for (i=1; (v = v >> 1) > 0; i++)
    ;
  return i;
}

/* rightrot: rotate x to the right by n positions */
unsigned rightrot_ans(unsigned x, int n) {
  int wordlength(void);
  int rbit;
  while(n-- > 0) {
    rbit = (x & 1) << (wordlength() - 1);
    x = x >> 1;
    x = x | rbit;
  }
  return x;
}

int main() {
  assert(rightrot(~0, 1) == ~0);
  assert(rightrot(~0, 0) == ~0);
  assert(rightrot(~0, 32) == ~0);
  assert(rightrot(~0, 16) == ~0);
  assert(rightrot(~0, 13) == ~0);
  assert(rightrot(0, 1) == 0);
  assert(rightrot(0, 0) == 0);
  assert(rightrot(0, 32) == 0);
  assert(rightrot(0, 16) == 0);
  assert(rightrot(0, 13) == 0);
  assert(rightrot(1, 1) == 0x80000000);
  assert(rightrot(0x80000001, 1) == 0xC0000000);

  assert(wordlength() == 32);

  int x1 = 218032241;
  assert(rightrot(x1, 0) == rightrot_ans(x1, 0));
  assert(rightrot(x1, 1) == rightrot_ans(x1, 1));
  assert(rightrot(x1, 2) == rightrot_ans(x1, 2));
  assert(rightrot(x1, 8) == rightrot_ans(x1, 8));
  assert(rightrot(x1, 13) == rightrot_ans(x1, 13));
  assert(rightrot(x1, 16) == rightrot_ans(x1, 16));
  assert(rightrot(x1, 31) == rightrot_ans(x1, 31));
  assert(rightrot(x1, 32) == rightrot_ans(x1, 32));
  assert(rightrot(x1, 33) == rightrot_ans(x1, 33));
  assert(rightrot(x1, 44) == rightrot_ans(x1, 44));
  assert(rightrot(x1, 63) == rightrot_ans(x1, 63));
  assert(rightrot(x1, 64) == rightrot_ans(x1, 64));
}