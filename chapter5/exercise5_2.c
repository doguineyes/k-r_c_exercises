/*
  Exercise 5-2 Write getfloat, the floating-point analog of getint.
*/
#include <ctype.h>
#include <stdio.h>

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

int getfloat(double *pn) {
  int h, c, sign;
  double power;
  while (isspace(c = getch())) {
    ;
  }
  if (!isdigit(c) && c != EOF && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }
  if (c == EOF) {
    return c;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '-') {
    c = getch();
  }
  h = c;
  *pn = 0.0;
  while(isdigit(c)) {
    *pn = 10.0 * *pn + (c - '0');
    c = getch();
  }
  if (c == '.') {
    c = getch();
  }
  power = 1.0;
  while(isdigit(c)) {
    *pn = 10.0 * *pn + (c - '0');
    power *= 10.0;
    c = getch();
  }
  ungetch(c);
  *pn = *pn * sign / power;
  return h;
}

int main() {
  double n = 0.0;
  int is_float = 0;
  while ((is_float = getfloat(&n)) != EOF) {
    printf("%d\n", is_float);
    if (is_float != 0) {
      printf("%f\n", n);
    } else {
      getch();
      printf("\n");
    }
  }
}