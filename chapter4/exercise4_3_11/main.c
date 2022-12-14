/*
  Exercise 4-3 Given the basic framework, it is straightforward to extend the calculator.
  Add the modulus (X) operator and provisions for negative numbers.

  Exercise 4-4 Add commands to print the top element of the stack without popping,
  to du­ plicate it, and to swap the top two elements. Add a command to clear the stack.

  Exercise 4-5 Add access to library functions like sin, exp, and pow.

  Exercise 4-6 Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.)
  Add a variable for the most recently printed value.
*/
#include <stdio.h>
#include <stdlib.h> // atof
#include <math.h> // for fmod, float mod; sin
#include <string.h>
#include "calc.h"

#define MAXOP 100

// Exercise 4-5
void handle_function(char func[]) {
  double op2;
  if (strcmp(func, "sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(func, "exp") == 0) {
    push(exp(pop()));
  } else if (strcmp(func, "pow") == 0) {
    op2 = pop();
    push(pow(pop(), op2));
  } else {
    printf("error: unknown function %s\n", func);
  }
}

int main() {
  int type;
  double op2;
  char s[MAXOP];
  // Exercise 4-6 add vars
  double vars[26];
  int last_var_index = 0;
  double v = 0.0;
  for (int i = 0; i < 26; i++) {
    vars[i] = 0.0;
  }

  // while((type = getop(s)) != EOF) {
  //Exercise 4-10
  // while((type = getop_line(s)) != EOF) {
  // Exercise 4-11
  while((type = getop_static(s)) != EOF) {
    switch(type) {
      case NUMBER:
        push(atof(s));
        break;
      case FUNCTION: // Exercise 4-5
        handle_function(s);
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
      // Exercise 4-6
      case '=':
        pop(); // Pop old vars name?
        vars[last_var_index] = pop();
        push(vars[last_var_index]); // If do not push variable assignment res, \n will have no value to pop
        break;
      case '\n':
        v = pop();
        printf("\t%.8g\n", v);
        break;
      default:
        // Exercise 4-6
        if (type >= 'A' && type <= 'Z') {
          last_var_index = type - 'A';
          push(vars[last_var_index]);
        } else if (type == 'v') {
          push(v);
        } else {
          printf("error: unknown command %s\n", s);
        }
        break;
    }
  }

  return 0;
}