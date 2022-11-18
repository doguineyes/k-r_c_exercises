/*
  Exercise 4-7 Write a routine ungets(s) that will push back an entire string onto the input.
  Should ungets know about buf and bufp, or should it just use ungetch?

  Exercise 4-8 Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
*/
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

//Exercise 4-8
char buf_s;
int has_buf = 0;

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

//Exercise 4-8
int getch_s(void) {
  if (has_buf != 0) {
    has_buf = 0;
    return buf_s;
  } else {
    return getchar();
  }
}

void ungetch_s(int c) {
  if (has_buf == 0) {
    buf_s = c;
    has_buf = 1;
  } else {
    printf("ungetch_s: only buff one character\n");
  }
}