/*
  Write the function htoi(s), which converts a string of hexadecimal digits
  (in­ cluding an optional 0x or 0X) into its equivalent integer value.
  The allowable digits are 0 through 9, a through f, and A through F.
*/
#include <string.h>
#include <assert.h>
#include <math.h>

enum boolean { TRUE, FALSE };

int isOX(char s[]) {
  if (strlen(s) <= 2) {
    return FALSE;
  }
  if (s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) {
    return FALSE;
  }
  char c;
  for (int i = 2; i < strlen(s); i++) {
    c = s[i];
    if (!(c >= '0' && c <='9') && !(c >= 'a' && c <= 'f') && !( c>= 'A' && c <= 'F')) {
      return FALSE;
    }
  }
  return TRUE;
}

int oneHtoI(char c) {
  if (!(c >= '0' && c <='9') && !(c >= 'a' && c <= 'f') && !( c>= 'A' && c <= 'F')) {
    return -1;
  }
  if (c >= '0' && c <='9') {
    return (c - '0');
  }
  switch (c) {
    case 'a': case 'A':
      return 10;
    case 'b': case 'B':
      return 11;
    case 'c': case 'C':
      return 12;
    case 'd': case 'D':
      return 13;
    case 'e': case 'E':
      return 14;
    case 'f': case 'F':
      return 15;
    default:
      return -1;
  }
}

int htoi(char s[]) {
  if (isOX(s) == FALSE) return -1;
  const int length = strlen(s);
  int res = 0;
  int power = 0;
  const int base = 16;
  for (int i = length - 1; i > 1; i--) {
    res += oneHtoI(s[i]) * pow(base, power);
    power++;
  }
  return res;
}

int main() {
  char s1[] = "0x1234";
  assert(isOX(s1) == TRUE);
  assert(htoi(s1) == 4660);

  char s2[] = "1234";
  assert(isOX(s2) == FALSE);

  char s3[] = "0X1FaaF";
  assert(isOX(s3) == TRUE);
  assert(htoi(s3) == 129711);

  char s4[] = "";
  assert(isOX(s4) == FALSE);

  char s5[] = "0xFF112Zss";
  assert(isOX(s5) == FALSE);

  char c0 = '0';
  assert(oneHtoI(c0) == 0);

  char c9 = '9';
  assert(oneHtoI(c9) == 9);

  char ca = 'a';
  assert(oneHtoI(ca) == 10);

  char cf = 'F';
  assert(oneHtoI(cf) == 15);

  char cz = 'Z';
  assert(oneHtoI(cz) == -1);

  char s6[] = "0xFFFF";
  assert(htoi(s6) == 65535);

  char s7[] = "0x0";
  assert(htoi(s7) == 0);

  char s8[] = "0x1";
  assert(htoi(s8) == 1);

  char s9[] = "0x1111";
  assert(htoi(s9) == 4369);
}