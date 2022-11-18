/*
  Write a function setbits(x, p, n, y) that returns x with the n bits 
  that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/
#include <stdio.h>
#include <assert.h>

int getIntBits() {
  return sizeof(int) * 8;
}

int setbits(int x, int p, int n, int y) {
  const int INT_BITS = getIntBits(); // 32
  if (p < 0 || p >= INT_BITS || n <= 0 || n > p + 1) {
    return x;
  }
  int maskX;
  if (p+1 == n) {
    maskX = (~01)<<p;
  } else {
    maskX = ((~01)<<p) | ~((~01)<<(p-n));
  }
  int maskY = ~((~01)<<(n-1));
  // printf("Setbits_1 p=%d, n=%d, Mask x=%x, mask y=%x\n", p, n, maskX, maskY);
  int result = (x & maskX) | (y & maskY) << (p + 1 - n);
  return result;
}

int getMaskX(int p, int n) {
  int maskX1 = (~0) << (p + 1);
  int maskX2 = ~((~0) << (p + 1 - n));
  int maskX = maskX1 | maskX2;
  // printf("Setbits_2 p=%d, n=%d, XMask1 %x, XMask2 %x, XMask %x\n", p, n, maskX1, maskX2, maskX);
  return maskX;
}

int getMaskY(int n) {
  int maskY = ~((~0)<<n);
  return maskY;
}

int setbits2(int x, int p, int n, int y) {
  const int INT_BITS = getIntBits(); // 32
  if (p < 0 || p >= INT_BITS || n <= 0 || n > p + 1) {
    return x;
  }
  int maskX = getMaskX(p, n);
  int maskY = getMaskY(n);
  printf("Setbits_2 p=%d, n=%d, Mask x=%x, mask y=%x\n", p, n, maskX, maskY);
  int result = (x & maskX) | (y & maskY)<<(p-n+1);
  return result;
}

/* setbits: set n bits of x at position p with bits of y */
unsigned setbits_ans(unsigned x , int p, int n, unsigned y){
  return (x & ~(~(~0 << n) << (p + 1 - n))) | (y & ~(~0 << n)) << (p + 1 - n);
}

int main() {
  int x0 = 0x8;
  int y0 = 0x9;
  printf("x %x, y %x, res %x\n", x0, y0, setbits(x0, 4, 3, y0));
  assert(setbits(x0, 4, 3, y0) == 4);
  printf("x %x, y %x, res2 %x\n", x0, y0, setbits2(x0, 4, 3, y0));
  assert(setbits2(x0, 4, 3, y0) == 4);
  printf("x %x, y %x, res ans %x\n", x0, y0, setbits_ans(x0, 4, 3, y0));
  assert(setbits_ans(x0, 4, 3, y0) == 4);
  printf("x %x, y %x, res %x\n", x0, y0, setbits(x0, 0, 1, y0));
  assert(setbits(x0, 0, 1, y0) == 9);
  printf("x %x, y %x, res %x\n", x0, y0, setbits(x0, 1, 2, y0));
  assert(setbits(x0, 1, 2, y0) == 9);
  printf("x %x, y %x, res %x\n", x0, y0, setbits(x0, 31, 32, y0));
  assert(setbits(x0, 31, 32, y0) == 9);
  printf("x %x, y %x, res %x\n", x0, y0, setbits(x0, 30, 31, y0));
  assert(setbits(x0, 30, 31, y0) == 9);
  printf("x %x, y %x, res %x\n", x0, y0, setbits(x0, 30, 1, y0));
  assert(setbits(x0, 30, 1, y0) == 0x40000008);
  printf("x %x, y %x, res2 %x\n", x0, y0, setbits2(x0, 30, 1, y0));
  assert(setbits2(x0, 30, 1, y0) == 0x40000008);
  printf("x %x, y %x, res ans %x\n", x0, y0, setbits_ans(x0, 30, 1, y0));
  assert(setbits_ans(x0, 30, 1, y0) == 0x40000008);

  int x = 218032241;
  int y = 216535677;
  assert(setbits(x, 0, 1, y) == setbits_ans(x, 0, 1, y));
  assert(setbits2(x, 0, 1, y) == setbits_ans(x, 0, 1, y));
  assert(setbits(x, 11, 7, y) == setbits_ans(x, 11, 7, y));
  assert(setbits2(x, 11, 7, y) == setbits_ans(x, 11, 7, y));
  printf("x %x, y %x, res ans %x\n", x, y, setbits(x, 31, 13, y));
  assert(setbits(x, 31, 13, y) == setbits_ans(x, 31, 13, y));
  // printf("x %x, y %x, res ans %x\n", x, y, setbits2(x, 31, 13, y));
  // assert(setbits2(x, 31, 13, y) == setbits_ans(x, 31, 13, y));
  printf("x %x, y %x, res %x\n", x, y, setbits(x, 31, 32, y));
  printf("x %x, y %x, res 2 %x\n", x, y, setbits2(x, 31, 32, y));
  printf("x %x, y %x, res ans %x\n", x, y, setbits_ans(x, 31, 32, y));
  printf("x %x, y %x, res %x\n", x, y, setbits(x, 13, 0, y));
  printf("x %x, y %x, res 2 %x\n", x, y, setbits2(x, 13, 0, y));
  printf("x %x, y %x, res ans %x\n", x, y, setbits_ans(x, 13, 0, y));
  // assert(setbits(x, 31, 32, y) == setbits_ans(x, 31, 32, y));
  assert(((~0u)<<31) == 0x80000000);
  assert(~((~01u)<<31) == ~0);
}
