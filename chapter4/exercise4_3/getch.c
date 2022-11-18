/*
  Exercise 4-7 Write a routine ungets(s) that will push back an entire string onto the input.
  Should ungets know about buf and bufp, or should it just use ungetch?
*/
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE];
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

//Exercise 4-7
void ungets(char s[]) {
  int i;
  for (i = strlen(s)-1; i >= 0; i--) {
    ungetch(s[i]);
  }
}