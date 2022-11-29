#include <stdio.h>
#include <string.h>

#define BUFSIZE 1000

static int buf[BUFSIZE];
static int bufp = 0;

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

void ungets(char s[]) {
  int i;
  for (i = strlen(s)-1; i >= 0; i--) {
    ungetch(s[i]);
  }
}

void clearbuf(void) {
  bufp = 0;
}