/*
  Exercise 5-6 Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
  Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3. and 4), reverse (Chapter 3), 
  and strlndex and getop (Chapter 4).
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>

/* getline: read a line into s, return length */
int getline_my(char *s, int lim) {
  if (s == NULL || lim <= 0) {
    return 0;
  }
  int c; // must be int, because char maybe can not hold EOF
  char *h = s;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *s++ = c;
  }
  if (c == '\n') {
    *s++ = c;
  }
  *s = '\0';
  return s - h;
}

/* atoi: convert a string to int */
int atoi_my(char *s) {
  if (s == NULL) return 0;
  int n = 0;
  int sign = 1;
  while(*s != '\0' && (*s == ' ' || *s == '\t'))
    s++;
  if (*s == '-') {
    sign = -1;
    s++;
  } else if (*s == '+') {
    sign = 1;
    s++;
  }
  while (*s != '\0' && isdigit(*s)) {
    n = n * 10 + (*s - '0');
    s++;
  }
  n *= sign;
  return n;
}

/* reverse: reverse string s in place */
void reverse(char *s) {
  if (s == NULL || *s == '\0') return;
  char* h = s;
  while (*s != '\0') {
    s++;
  }
  if (s == h)
    return;
  s--;
  char c;
  while (h < s) {
    c = *h;
    *h = *s;
    *s = c;
    h++;
    s--;
  }
  return;
}

/* itoe: convert n to characters in s; pointer version */
void itoa(int n, char *s) {
  char *h = s;
  int sign = n < 0 ? -1 : 1;
  do {
    *s = abs(n % 10) + '0';
    n /= 10;
    s++;
  } while (n != 0);
  if (sign < 0) {
    *s++ = '-';
  }
  *s = '\0';
  reverse(h);
}

/* strlndex: return index of t in s, -1 If none */
int strindex(char *s, char *t) {
  if (s == NULL || t == NULL || *s == '\0' || *t == '\0') {
    return -1;
  }
  char *thead = t;
  char *shead = s;
  char *ps;
  while(*s != '\0') {
    if (*s == *thead) {
      ps = s;
      while (*t != '\0') {
        if (*ps == '\0' || *ps++ != *t++) {
          break;
        }
      }
      if (*t == '\0') {
        return s - shead;
      }
    }
    s++;
  }
  return -1;
}

int main() {
  assert(atoi_my("13") == 13);
  assert(atoi_my("-1") == -1);
  assert(atoi_my("-13") == -13);
  assert(atoi_my("0") == 0);
  assert(atoi_my("2147483647") == INT_MAX);
  assert(atoi_my("-2147483648") == INT_MIN);
  
  char s1[] = "hello !";
  reverse(s1);
  assert(strcmp(s1, "! olleh") == 0);

  char s2[] = "h";
  reverse(s2);
  assert(strcmp(s2, "h") == 0);

  char s3[] = "";
  reverse(s3);
  assert(strcmp(s3, "") == 0);

  char s[100];
  itoa(13, s);
  assert(strcmp(s, "13") == 0);
  itoa(-13, s);
  assert(strcmp(s, "-13") == 0);
  itoa(0, s);
  assert(strcmp(s, "0") == 0);
  itoa(INT_MIN, s);
  assert(strcmp(s, "-2147483648") == 0);
  itoa(INT_MAX, s);
  assert(strcmp(s, "2147483647") == 0);

  assert(strindex("", "hello") == -1);
  assert(strindex("hello", "") == -1);
  assert(strindex("hello world", "wor") == 6);
  assert(strindex("hello world world world ?!", "wor") == 6);
  assert(strindex("hello wor", "hello world") == -1);
  assert(strindex("hello world", "hello") == 0);
  assert(strindex("hello world", "world") == 6);
}