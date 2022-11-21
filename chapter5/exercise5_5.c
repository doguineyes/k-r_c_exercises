/*
 Exercise 5-5 Write the versions of the library functions strncpy, strncat, and strncmp,
which operate on at most the first n characters of their argument strings.
For example, strncpy(s, t, n) copies at most n characters of t to s. Full de­ scriptions are in Appendix B (page 249 K&R).
*/
#include <assert.h>
#include <string.h>

void strncpy_my(char *s, char *t, int n) {
  for (int i = n; i > 0; i--) {
    if (*t == '\0') {
      *s++ = '\0';
    } else {
      *s++ = *t++;
    }
  }
}

void strncpy_ans(char *s, char *t, int n) {
  while (*t && n-- > 0) {
    *s++ = *t++;
  }
  while (n-- > 0) {
    *s++ = '\0';
  }
}

void strncat_my(char *s, char *t, int n) {
  if (n <= 0) {
    return;
  }
  while(*s) {
    s++;
  }
  while(n > 0) {
    n--;
    if ((*s++ = *t++) == '\0')
      break;
  }
  if (n == 0) {
    *s = '\0';
  }
}

void strncat_ans(char *s, char *t, int n) {
  void strncpy_ans(char *, char *, int);
  strncpy_ans(s + strlen(s), t, n);
}

int strncmp_my(char *s, char *t, int n) {
  for (; n > 0 && *s == *t; s++, t++, n--) {
    if (*s == '\0') {
      return 0;
    }
  }
  if (n == 0) {
    return 0;
  }
  return *s - *t;
}

int strncmp_ans(char *s, char *t, int n) {
  for (; *s == *t; s++, t++) {
    if (*s == '\0' || --n <= 0) {
      return 0;
    }
  }
  return *s - *t;
}

int main() {
  char s[100] = "";
  strncpy_my(s, "hello world!", 0);
  assert(strcmp(s, "") == 0);
  strncpy_my(s, "hello world!", 5);
  assert(strcmp(s, "hello") == 0);
  strncpy_my(s, "hello world!", 20);
  assert(strcmp(s, "hello world!") == 0);

  char s1[100] = "";
  strncat_my(s1, "hello world!", 0);
  assert(strcmp(s1, "") == 0);
  strncat_my(s1, "hello world!", 5);
  assert(strcmp(s1, "hello") == 0);
  strncat_my(s1, "hello world!", 20);
  assert(strcmp(s1, "hellohello world!") == 0);

  assert(strncmp_my("hello world!", "helww", 3) == 0);
  assert(strncmp_my("helww", "hello world!", 3) == 0);
  assert(strncmp_my("", "hello world!", 3) < 0);
  assert(strncmp_my("hello world!", "", 3) > 0);
  assert(strncmp_my("helww", "helww", 10) == 0);
  assert(strncmp_my("helww", "helww", 5) == 0);
  assert(strncmp_my("hello", "helaa", 5) > 0);
  assert(strncmp_my("helaa", "hello", 5) < 0);
}