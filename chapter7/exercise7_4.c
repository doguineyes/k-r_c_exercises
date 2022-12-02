/*
  Exercise 7-4 Write a private version of scanf analogous to minprintf from the previous section.
*/
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCALFMT 100

int miniscanf(char* fmt, ...) {
  va_list ap;
  char c;
  char* p;
  char* sval;
  int* pival;
  float* pfval;
  char localfmt[LOCALFMT];

  int n = 0;

  int i = 0;
  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      localfmt[i++] = *p;
      continue;
    }
    localfmt[i++] = '%';
    while (*(p+1) && !isalpha(*(p+1))) {
      localfmt[i++] = *++p;
    }
    localfmt[i++] = *(p+1);
    localfmt[i] = '\0';
    printf("localfmt: %s\n", localfmt);
    switch(*++p) {
      case 'd':
        pival = va_arg(ap, int*);
        scanf(localfmt, pival);
        n++;
        break;
      case 'f':
        pfval = va_arg(ap, float*);
        scanf(localfmt, pfval);
        n++;
        break;
      case 's':
        sval = va_arg(ap, char*);
        scanf(localfmt, sval);
        n++;
        break;
      default:
        scanf(localfmt, NULL);
        break;
    }
    i=0;
  }
  va_end(ap);
  return n;
}

int main() {
  int a;
  int b;
  float c;
  float d;
  char s[100];
  miniscanf("a = %d b = %d c = %f d = %f s=%s", &a, &b, &c, &d, s);
  printf("a: %d, b: %d, c: %f, d: %f, s: %s", a, b, c, d, s);
}