/*
  Exercise 7-9 Functions like isupper can be implemented to save space or to save time. Explore both possibilities.
*/
#include <assert.h>
#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

int main() {
  assert(isupper('a') == 0);
  assert(isupper('9') == 0);
  assert(isupper('A') == 1);
  assert(isupper('T') == 1);
  assert(isupper('Z') == 1);
}