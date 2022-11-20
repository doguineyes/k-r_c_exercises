/*
  Exercise 5-1 As written, get int treats a + or - not followed by a digit as a valid representation of zero.
  Fix it to push such a character back on the input.
*/
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
int buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

int getint(int *pn) {
  int c, sign;
  while(isspace(c = getch())) {
    ;
  }
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '-' || c == '+') {
    char c_next = getch();
    if (!isdigit(c_next)) {
      ungetch(c);
      ungetch(c_next);
      return 0;
    } else {
      c = c_next;
    }
  }
  for (*pn = 0; isdigit(c); c=getch()) {
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}

int main() {
  int n = 0;
  int is_int = 0;
  while ((is_int = getint(&n)) != EOF) {
    if (is_int != 0) {
      printf("%d\n", n);
    } else {
      getch();
      getch();
      printf("\n");
    }
  }
}