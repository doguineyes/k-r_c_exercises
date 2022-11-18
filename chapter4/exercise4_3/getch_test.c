#include <assert.h>
#include "calc.h"

int main() {
  char s[] = "hello";
  ungets(s);
  assert(getch() == 'h');
  assert(getch() == 'e');
}