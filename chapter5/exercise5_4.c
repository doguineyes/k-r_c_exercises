/*
  Exercise 5-4 Write the function strend(s, t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.
*/
#include <assert.h>
#include <string.h>

int strend(char* s, char* t) {
  int slen = 0;
  int tlen = 0;
  const char* thead = t;
  while (*s) {
    s++;
    slen++;
  }
  while (*t) {
    t++;
    tlen++;
  }
  if (slen < tlen || tlen == 0) {
    return 0;
  }
  while (t != thead) {
    if (*--t != *--s) {
      return 0;
    }
  }
  return 1;
}

int main() {
  assert(strend("hello world!", "world!") == 1);
  assert(strend("hello world!", "d!") == 1);
  assert(strend("hello world!", "") == 0);
  assert(strend("hello world!", "error") == 0);
  assert(strend("hello world!", "hello world!") == 1);
  assert(strend("", "hello world!") == 0);
  assert(strend("", "") == 0);
}