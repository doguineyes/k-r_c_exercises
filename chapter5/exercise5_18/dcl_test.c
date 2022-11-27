#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "dcl.h"
#include "dcl_test.h"

int main() {
  char s[] = "      (*pfa[])()";
  ungets(s);
  assert(strcmp(gettoken_test(), "") == 0);
  assert(gettoken() == '(');
  assert(strcmp(gettoken_test(), "") == 0);
  assert(gettoken() == '*');
  assert(strcmp(gettoken_test(), "") == 0);
  assert(gettoken() == NAME);
  assert(strcmp(gettoken_test(), "pfa") == 0);
  assert(gettoken() == BRACKETS);
  assert(strcmp(gettoken_test(), "[]") == 0);
  assert(gettoken() == ')');
  assert(strcmp(gettoken_test(), "[]") == 0);
  assert(gettoken() == PARENS);
  assert(strcmp(gettoken_test(), "()") == 0);

  char s1[] = "char (*(*x[3])())[5]\n";
  ungetch(EOF);
  ungets(s1);
  assert(dcl_main() == 0);
}