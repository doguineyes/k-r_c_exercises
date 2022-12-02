/*
  Exercise 7-1 Write a program that converts upper case to lower case or lower case to upper,
  depending on the name it is invoked with, as found in argv[0].
*/
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int trans(int argc, char* argv[]) {
  int (*f)(int) = NULL;

  if (strstr(argv[0], "utol") != NULL) {
    f = tolower;
  } else if (strstr(argv[0], "ltou") != NULL) {
    f = toupper;
  } else {
    return -1;
  }

  int c;
  while ((c = getchar()) != EOF) {
    putchar(f(c));
  }
  return 0;
}

int main(int argc, char*argv[]) {
  return trans(argc, argv);
}