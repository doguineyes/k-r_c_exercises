#include <assert.h>
#include <stdio.h>
#include "calc.h"

int main() {
  // char s[200];
  // while (getword(s) > 0) {
  //   printf("{%s}\n", s);
  // }

  char func[] = "sin";
  assert(is_func(func) != 0);
  assert(is_num(func) == 0);

  char num1[] = "13";
  char num2[] = "-.33303";
  char num3[] = ".900";
  char num4[] = "-13.00";
  char num5[] = "-99";
  assert(is_num(num1) != 0);
  assert(is_num(num2) != 0);
  assert(is_num(num3) != 0);
  assert(is_num(num4) != 0);
  assert(is_num(num5) != 0);

  char num99[] = "-.33.11";
  assert(is_num(num99) == 0);
}