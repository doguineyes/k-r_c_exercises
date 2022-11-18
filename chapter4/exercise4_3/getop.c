#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
  int i, c, c_next;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }
  i = 0;
  // handle negative numbers
  if (c == '-') {
    if(isdigit(c_next = getch()) || c_next == '.') { // support .3 is 0.3, or -.3 is -0.3
      s[++i] = c_next;
      c = c_next;
    } else {
      if (c != EOF) { // need check c != eof, why?
        ungetch(c_next);
      }
      return c;
    }
  }
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  s[i] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}