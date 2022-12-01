#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "exercise6_5.h"

int main() {
  install("hello", "1");
  install("world", "2");
  install("odd", "3");
  install("bug", "4");
  nlistprint();
  assert(strcmp(lookup("hello")->defn, "1") == 0);

  undef("bug", "4");
  assert(lookup("odd") != NULL);
  assert(lookup("world") != NULL);
  assert(lookup("bug") == NULL);
  assert(lookup("hello") != NULL);
  nlistprint();

  undef("odd", "3");
  assert(lookup("odd") == NULL);
  assert(lookup("world") != NULL);
  assert(lookup("bug") == NULL);
  assert(lookup("hello") != NULL);
  nlistprint();

  install("bug", "4");
  install("odd", "3");
  nlistprint();
  undef("world", "2");
  assert(lookup("odd") != NULL);
  assert(lookup("world") == NULL);
  assert(lookup("bug") != NULL);
  assert(lookup("hello") != NULL);
  nlistprint();
  undef("hello", "1");
  assert(lookup("odd") != NULL);
  assert(lookup("world") == NULL);
  assert(lookup("bug") != NULL);
  assert(lookup("hello") == NULL);
  nlistprint();
}