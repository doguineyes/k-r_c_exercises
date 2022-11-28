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

  char s2[] = "(*(*x[3])())[5]\n";
  ungetch(EOF);
  ungets(s2);
  assert(dcl_main() == -1);

  char s3[] = "char (*pfa[]\n";
  ungetch(EOF);
  ungets(s3);
  assert(dcl_main() == -1);

  char s4[] = "char ()[]\n";
  ungetch(EOF);
  ungets(s4);
  assert(dcl_main() == -1);
}