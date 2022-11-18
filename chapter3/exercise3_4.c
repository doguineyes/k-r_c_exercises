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

void itoa(int n, char s[]) {
  if (n == INT_MIN) {
    strcpy(s, "-2147483648");
    return;
  }
  int i, sign;
  if ((sign = n) < 0) {
    n = -n;
  }
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

void itoa_ans(int n, char s[]) {
  int i, sign;
  sign = n;
  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while ((n /= 10) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  char s[100];
  itoa(1234, s);
  assert(strcmp(s, "1234") == 0);

  itoa(-1234, s);
  assert(strcmp(s, "-1234") == 0);

  // printf("INT_MAX: %d, INT_MIN: %d\n", INT_MAX, INT_MIN);
  itoa(INT_MIN, s);
  // printf("itoa(INT_MIN, s) = %s\n", s);
  assert(strcmp(s, "-2147483648") == 0);

  itoa_ans(INT_MIN, s);
  // printf("itoa_ans(INT_MIN, s) = %s\n", s);
  assert(strcmp(s, "-2147483648") == 0);
}