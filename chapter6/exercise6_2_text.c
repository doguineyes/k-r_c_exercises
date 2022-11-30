#include <assert.h>
#include <stdio.h>
#include "exercise6_2_test.h"
#include "getch.h"

int main(void) {
  char s1[] = "hello helcc helww 123 workk your world wordd heljj workk heljj";
  ungetch(EOF);
  ungets(s1);

  int argc = 2;
  char argv0[] = "treex";
  char argv1[] = "-3";
  char* argv[] = { argv0, argv1 };
  treex_main(argc, argv);
}