#include <stdio.h>
#include "calc.h"
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

// Exercise 4-4

// Get top element but do not pop
double top(void) {
  if (sp > 0)
    return val[sp - 1];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

// Clear the stack
void clear(void) {
  sp = 0;
}