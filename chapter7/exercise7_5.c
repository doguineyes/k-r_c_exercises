/*
  Exercise 7-5 Rewrite the postfix calculator of Chapter4 to use scanf and/or sscanf to do the input and number conversion.
*/
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "../chapter6/getch.h"

#define NUMBER '0'

int getop(char s[]) {
  char c;
  int i, rc;
  static char lastc[] = " "; //len = 2

  sscanf(lastc, "%c", &c);
  lastc[0] = ' '; //clear last character
  while ((s[0] = c) == ' ' || c == '\t') {
    if (scanf("%c", &c) == EOF) {
      c = EOF;
    }
  }
  s[1] = '\0';
  if (!isdigit(c) && c != '.') {
    return c; // not a number
  }
  i = 0;
  // collect integer part
  if (isdigit(c)) {
    do {
      rc = scanf("%c", &c);
      if (!isdigit(s[++i] = c)) {
        break;
      }
    } while (rc != EOF);
  }
  // collect fraction part
  if (c == '.') {
    do {
      rc = scanf("%c", &c);
      if (!isdigit(s[++i] = c)) {
        break;
      }
    } while (rc != EOF);
  }
  s[i] = '\0';
  if (rc != EOF) {
    lastc[0] = c;
  }
  return NUMBER;
}

int main() {
  char op[100];
  char r;
  while (1) {
    r = getop(op);
    printf("op is: %s, r is: %c\n", op, r);
  }
}