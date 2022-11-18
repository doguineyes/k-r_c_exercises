/**
 * K&R C Exec 1-20
 * by Doguin
*/
#include <stdio.h>
#include <limits.h>

#define N 4 //One tab termination every n columns
#define TOO_LONG_LINE -2

void putSpaces(int n) {
  if (n <= 0 || n > N) return;
  for (int i = 0; i < n; i++) {
    putchar(' ');
  }
}

int main() {
  long countInLine = 0;
  int c = 0;
  int needAddSpace = 0;
  char s[] = "Hello // world /* thank you! */";
  while((c = getchar()) != EOF) {
    if(countInLine >= (LONG_MAX - N) || countInLine < 0) {
      return TOO_LONG_LINE;
    }
    countInLine++;
    if (c == '\n') {
      countInLine = 0;
      putchar(c);
    } else if (c == '\t') {
      needAddSpace = N - (countInLine % N);
      if(needAddSpace == N)
        needAddSpace = 0;
      countInLine = countInLine + needAddSpace;
      putSpaces(needAddSpace + 1);
    } else {
      putchar(c);
    }
  }
}