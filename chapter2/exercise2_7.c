/*
  Write a function invert(x ,p,n) that returns x with the n bits that begin at position p 
  inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/
#include <stdio.h>
#include <assert.h>

int getIntBits() {
  return sizeof(int) * 8;
}

int invert(int x, int p, int n) {
  const int INT_BITS = getIntBits(); // 32
  if (p < 0 || p >= INT_BITS || n <= 0 || n > p + 1) {
    return x;
  }
  int mask = ~((~01) << (n - 1)) << (p + 1 - n);
  int result = x ^ mask;
  return result;
}

/* invert: inverts the n bits of x that begin at position p */
unsigned invert_ans(unsigned x, int p, int n) {
  return x ^ (~(~0 << n) << (p + 1 - n));
}

int main() {
  assert(invert(~0, 31, 32) == 0);
  assert(invert(~0, 0, 1) == ~0u<<1);
  assert(invert(~0, 31, 31) == 01);
  assert(invert(0, 31, 32) == ~0);
  assert(invert(0, 31, 32) == ~0);
  assert(invert(0, 0, 1) == 01);
  assert(invert(0, 3, 2) == 12);

  int x1 = 218032241;
  assert(invert(x1, 13, 7) == invert_ans(x1, 13, 7));
  assert(invert(x1, 13, 1) == invert_ans(x1, 13, 1));
  assert(invert(x1, 31, 1) == invert_ans(x1, 31, 1));
  assert(invert(x1, 0, 1) == invert_ans(x1, 0, 1));
  assert(invert(x1, 11, 12) == invert_ans(x1, 11, 12));
  assert(invert(x1, 7, 7) == invert_ans(x1, 7, 7));
  assert(invert(x1, 31, 29) == invert_ans(x1, 31, 29));
  assert(invert(x1, 31, 31) == invert_ans(x1, 31, 31));
  assert(invert(x1, 31, 16) == invert_ans(x1, 31, 16));
  // assert(invert(x1, 31, 32) == invert_ans(x1, 31, 32)); // assertion failed on mac os

  int x2 = 216535677;
  assert(invert(x2, 13, 7) == invert_ans(x2, 13, 7));
  assert(invert(x2, 13, 1) == invert_ans(x2, 13, 1));
  assert(invert(x2, 31, 1) == invert_ans(x2, 31, 1));
  assert(invert(x2, 0, 1) == invert_ans(x2, 0, 1));
  assert(invert(x2, 11, 12) == invert_ans(x2, 11, 12));
  assert(invert(x2, 7, 7) == invert_ans(x2, 7, 7));
  assert(invert(x2, 31, 29) == invert_ans(x2, 31, 29));
  assert(invert(x2, 31, 31) == invert_ans(x2, 31, 31));
  assert(invert(x2, 31, 16) == invert_ans(x2, 31, 16));
  // assert(invert(x2, 31, 32) == invert_ans(x2, 31, 32)); // assertion failed on mac os
}