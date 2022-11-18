#include <assert.h>
#include "calc.h"

int main() {
  char s[] = "hello";
  ungets(s);
  assert(getch() == 'h');
  assert(getch() == 'e');

  ungetch_s('h');
  ungetch_s('e');
  ungetch_s('l');
  assert(getch_s() == 'h');
}