/**
  Write a loop equivalent to the for loop above without using && or || .
  Original :
  for (i=O; i<lim-1 && (c=getchar()) != '\n' && c != EOF; i++)
*/

#include <stdio.h>

int main() {
  char c;
  const int limit = 100;
  int i = 0;
  char s[limit];
  // equivalent for
  while((c = getchar()) != EOF) {
    if (i >= limit-1) {
      break;
    }
    if (c == '\n') {
      break;
    }
    s[i] = c;
    i++;
  }
  s[i] = '\0';
  printf("S: %s\n", s);
}