/*
  Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned,
  by printing appropriate values from standard headers and by direct computation.
  Harder if you compute them: determine the ranges of the various floating-point types.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>

void charRange(void);
void unsignedCharRange(void);
char computeMinChar(void);
char computeMaxChar(void);

char computeMinChar() {
  char c = -1;
  while(((char)(c-1)) < 0) {
    c--;
  }
  return c;
}

char computeMaxChar() {
  char c = 1;
  while(((char)(c+1)) > 0) {
    c++;
  }
  return c;
}

int computeMinInt() {
  int x = -1;
  while(x-1 < 0) {
    x--;
  }
  return x;
}

int computeMaxInt() {
  int x = 1;
  while(x+1 > 0) {
    x++;
  }
  return x;
}

int main() {
  charRange();
  unsignedCharRange();
  printf("Int min is %d, max is %d\n", INT_MIN, INT_MAX);
  printf("Unsigned int max is %u\n", UINT_MAX);
  // printf("Compute min int is %d, max int is %d\n", computeMinInt(), computeMaxInt());
  printf("Bitwise min int is %d, max int is %d\n", -(int)((unsigned int)~0 >> 1), (int)((unsigned int)~0 >> 1));
  printf("Bitwise unsigned int max is %u\n", (unsigned int)~0);
  printf("Long min is %ld, max is %ld\n", LONG_MIN, LONG_MAX);
  printf("Unsigned long max is %lu\n", ULONG_MAX);
  printf("Bitwise unsigned long max is %lu\n", (unsigned long)~0);
  printf("Float min is %e, max is %e, epsilon is %e\n", FLT_MIN, FLT_MAX, FLT_EPSILON);
  printf("Double min is %e, max is %e, epsilon is %e\n", DBL_MIN, DBL_MAX, DBL_EPSILON);
}

void charRange(void) {
  printf("Signed char min is %d, max is %d\n", CHAR_MIN, CHAR_MAX);
  // printf("Compute signed char min is %d, max is %d\n", computeMinChar(), computeMaxChar());
  printf("Compute by bitwise signed char min is %d, max is %d\n", -(char)((unsigned char)~0 >> 1), (char)((unsigned char)~0 >> 1));
}

void unsignedCharRange(void) {
  printf("Unsigned char max is %d\n", UCHAR_MAX);
}