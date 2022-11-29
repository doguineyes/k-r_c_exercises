#include <assert.h>
#include <stdio.h>
#include "getch.h"

int main() {
  char s[] = "hello";
  ungets(s);
  assert(getch() == 'h');
  assert(getch() == 'e');

  clearbuf();
  ungetch(EOF);
  assert(getch() == EOF);
}