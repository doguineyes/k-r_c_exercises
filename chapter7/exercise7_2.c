/*
  Exercise 7-2 Write a program that will print arbitrary input in a sensible way.
  As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int beautiprint(int argc, char* argv[]) {
  int c;
  int n = 0;
  int iso = 0;
  if (argc > 1 && strcmp(argv[1], "-o") == 0) {
    iso = 1;
  }

  while ((c = getchar()) != EOF) {
    if (isprint(c) || c == '\n') {
      printf("%c", c);
    } else if (iso == 0) {
      printf("%x", c);
    } else {
      printf("%o", c);
    }
    if (n > MAXLINE) {
      printf("\n");
      n = 0;
    }
    n++;
  }

  return 0;
}

int main(int argc, char* argv[]) {
  return beautiprint(argc, argv);
}