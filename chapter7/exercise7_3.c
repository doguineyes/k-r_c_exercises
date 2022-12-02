/*
  Exercise 7-3 Revise minprintf to handle more of the other facilities of printf.
*/
#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...) {
  va_list ap;
  char* p;
  char* sval;
  int ival;
  double dval;
  char cval;

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch(*++p) {
      case 'd': case 'i':
        ival = va_arg(ap, int);
        printf("%d", ival);
        break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
        break;
      case 's':
        for (sval = va_arg(ap, char*); *sval; sval++) {
          putchar(*sval);
        }
        break;
      case 'c':
        cval = va_arg(ap, int);
        putchar(cval);
        break;
      case 'o':
        ival = va_arg(ap, int);
        printf("%o", ival);
        break;
      case 'x': case 'X':
        ival = va_arg(ap, int);
        printf("%x", ival);
        break;
      default:
        putchar(*p);
        break;
    }
  }
  va_end(ap);
}

int main(void) {
  minprintf("hello %d world %f you %s char %c oct %o x0 %x\n", 913, 1.0001, "hello 123", '$', 1923, 2391923);
}