#include <assert.h>
#include <stdio.h>
#include "dcl.h"

int main() {
  ungetch('h');
  ungetch('e');
  ungetch('l');
  ungetch(EOF);
  assert(getch() == EOF);
  assert(getch() == 'l');
}