/*
  Exercise 4-3 Given the basic framework, it is straightforward to extend the calculator.
  Add the modulus (X) operator and provisions for negative numbers.

  Exercise 4-4 Add commands to print the top element of the stack without popping,
  to du­ plicate it, and to swap the top two elements. Add a command to clear the stack.
*/
#include <stdio.h>
#include <stdlib.h> // atof
#include <math.h> // for fmod, float mod
#include "calc.h"

#define MAXOP 100

int main() {
  int type;
  double op2;
  char s[MAXOP];

  while((type = getop(s)) != EOF) {
    switch(type) {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0) {
          push(pop() / op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      // exercise 4-3
      case '%':
        op2 = pop();
        if (op2 != 0.0) {
          // push((int)pop() % (int)op2);
          push(fmod(pop(), op2));
        } else {
          printf("error: zero divisor\n");
        }
        break;
      // exercise 4-4
      case '?':
        //Get top but do not pop
        printf("\t%.8g\n", top());
        break;
      case 'c':
        //Clear the stack
        clear();
        break;
      case 'd':
        //Duplicate the top
        op2 = pop();
        push(op2);
        push(op2);
        break;
      case 's':
        //Switch the top two
        op2 = pop();
        double op1 = pop();
        push(op2);
        push(op1);
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }

  return 0;
}