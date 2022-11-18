/*
  Rewrite the function Lawer, which converts upper case letters to lower case,
  with a conditional expression instead of if-else".
*/
#include <assert.h>

int lower(int c) {
  return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int main() {
  assert(lower('A') == 'a');
  assert(lower('a') == 'a');
  assert(lower('Z') == 'z');
  assert(lower('z') == 'z');
  assert(lower('B') == 'b');
  assert(lower('F') == 'f');
}