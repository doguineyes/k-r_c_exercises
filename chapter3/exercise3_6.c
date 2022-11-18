/*
  Write a version of itoa that acpts three arguments instead of two.
  The third argument is a minimum field width;
  the converted number must be padded with blanks on the left if necessary to make it wide enough.
*/
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char s[], int w) {
  int i, sign;
  sign = n;
  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while ((n /= 10) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  while (i < w) {
    s[i++] = ' ';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  char s[100];
  itoa(1234, s, 5);
  assert(strcmp(s, " 1234") == 0);

  itoa(-1234, s, 5);
  assert(strcmp(s, "-1234") == 0);

  itoa(INT_MIN, s, 13);
  assert(strcmp(s, "  -2147483648") == 0);

  itoa(INT_MIN, s, 1);
  assert(strcmp(s, "-2147483648") == 0);
}