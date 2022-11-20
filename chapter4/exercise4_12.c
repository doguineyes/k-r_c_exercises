/*
  Exercise 4-12 Adapt the ideas of printd to write a recursive version of itoa;
  that is convert an integer into a string by calling a recursive routine.
*/
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#define abs(x) ((x) < 0 ? -(x) : (x))

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa_r(int n, char s[], int pos, int sign) {
  s[pos] = abs(n % 10) + '0';
  if ((n / 10) == 0) {
    if (sign < 0) {
      s[++pos] = '-';
    }
    s[++pos] = '\0';
    return;
  } else {
    itoa_r(n / 10, s, pos+1, sign);
  }
}

void itoa(int n, char s[]) {
  int sign = (n < 0) ? -1 : 1;
  itoa_r(n, s, 0, sign);
  reverse(s);
}

void itoa_ans(int n, char s[]) {
  static int i;
  if (n / 10 != 0) {
    itoa_ans(n / 10, s);
  } else {
    i = 0;
    if (n < 0) {
      s[i++] = '-';
    }
  }
  s[i++] = abs(n % 10) + '0';
  s[i] = '\0';
}

int main() {
  char s[100];
  itoa(19, s);
  assert(strcmp(s, "19") == 0);
  itoa(-19, s);
  assert(strcmp(s, "-19") == 0);
  itoa(INT_MIN, s);
  assert(strcmp(s, "-2147483648") == 0);
  itoa(INT_MAX, s);
  assert(strcmp(s, "2147483647") == 0);
  itoa(0, s);
  assert(strcmp(s, "0") == 0);
  itoa(-0, s);
  assert(strcmp(s, "0") == 0);

  itoa_ans(19, s);
  assert(strcmp(s, "19") == 0);
  itoa_ans(INT_MIN, s);
  assert(strcmp(s, "-2147483648") == 0);
  itoa_ans(INT_MAX, s);
  assert(strcmp(s, "2147483647") == 0);
  itoa_ans(0, s);
  assert(strcmp(s, "0") == 0);
}