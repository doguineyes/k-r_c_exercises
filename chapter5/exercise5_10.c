/*
  Exercise 5-10 Write the program expr, which evaluates a reverse Polish expression from the command line,
  where each operator or operand is a separate argument. For example,
  expr 2 3 4 + \*
  evaluate 2 * (3 + 4)
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXVAL 100
#define NUMBER '0'

static int sp = 0;
static double val[MAXVAL];

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

int is_num(char s[]) {
  if (!isdigit(s[0]) && s[0] != '.' && s[0] != '-') {
    return 0;
  }
  int dot_num = 0;
  int num_num = 0;
  if (s[0] == '.') {
    dot_num = 1;
  } else if (isdigit(s[0])){
    num_num = 1;
  }
  for (int i = 1; s[i] != '\0'; i++) {
    if (isdigit(s[i])) {
      num_num++;
    } else if (s[i] == '.') {
      dot_num++;
    } else {
      return 0;
    }
  }
  return (num_num >= 1 && dot_num <= 1) ? 1 : 0;
}

int getop(char s[]) {
  // printf("getop by: %s\n", s);
  if (is_num(s)) {
    return NUMBER;
  } else {
    return s[0];
  }
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Usage: expr 2 3 + 4 5 \\* \\/\n");
    return -1;
  }
  // for (int i = 0; i < argc; i++) {
  //   printf("arg%d is %s\n", i, argv[i]);
  // }
  int opn = argc - 1;
  char **ops = argv + 1;
  double op2 = 0.0;
  int type;
  while (opn-- > 0) {
    type = getop(*ops);
    // printf("Type is %c\n", type);
    switch(type) {
      case NUMBER:
        push(atof(*ops));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '*':
        push(pop() * pop());
        break;
      case '/':
        op2 = pop();
        push(pop() / op2);
        break;
      default:
        printf("Do not know option: %s", *ops);
        return -1;
    }
    ops++;
  }
  printf("%.8f\n", pop());
  return 0;
}