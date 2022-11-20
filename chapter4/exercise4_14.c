/*
  Exercise 4-14 Define a macro swap(t, x, y) that interchanges two arguments of type t.
  (Block structure will help.)
*/
#include <assert.h>
#define swap(t, x, y) { t c = x; x = y; y = c; }

int main() {
  int x1 = 13;
  int y1 = 14;
  swap(int, x1, y1);

  assert(x1 = 14);
  assert(y1 = 13);
}