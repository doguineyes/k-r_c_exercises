/*
  Write the function itob(n, s, b) that converts the integer n into a base b character representation
  in the string s. In particular, itob(n, s, 16) formats n as a hexadecimal integer in s.
*/
#include <string.h>
#include <assert.h>
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

/* b from 2 to 16 */
void itob(int n, char s[], int b) {
  if (b < 2 || b > 16) {
    s[0] = '\0';
    return;
  }
  char v[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  int i, sign;
  sign = n;
  i = 0;
  do {
    // int v = abs(n % b);
    // s[i++] = (v <= 9) ? (v + '0') : (v + 'A' - 10);
    s[i++] = v[abs(n % b)];
  } while ((n /= b) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  int n1 = 13;
  char s[100];
  itob(n1, s, 2);
  assert(strcmp(s, "1101")  == 0);
  itob(n1, s, 3);
  assert(strcmp(s, "111")  == 0);
  itob(n1, s, 8);
  assert(strcmp(s, "15")  == 0);
  itob(n1, s, 16);
  assert(strcmp(s, "D")  == 0);

  int n2 = INT_MIN;
  itob(n2, s, 16);
  assert(strcmp(s, "-80000000") == 0);

  int n3 = INT_MAX;
  itob(n3, s, 8);
  assert(strcmp(s, "17777777777") == 0);
}