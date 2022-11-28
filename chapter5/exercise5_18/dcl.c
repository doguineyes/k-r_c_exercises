/*
  Exercise 5-18 Make dcl recover from input errors.

  Exercise 5-19 Modify undcl so that it does not add redundant parentheses to declarations.
*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dcl.h"

#define MAXTOKEN 100

enum { ERROR, NORMAL };

enum { NO, YES };

static int iserror = NORMAL;

static int prevtoken = NO;

void dcl(void);
void dirdcl(void);
void error(char*);

//use by gettoken
static int tokentype;
static char token[MAXTOKEN] = {'\0'};

//use by dcl and dirdcl
static char name[MAXTOKEN] = {'\0'};
static char datatype[MAXTOKEN] = {'\0'};
static char out[1000] = {'\0'};

char* gettoken_test(void) {
  return token;
}

int gettoken(void) {
  int c;
  int getch(void);
  void ungetch(int);
  char *p = token;

  if (prevtoken == YES) {
    prevtoken = NO;
    return tokentype;
  }

  while ((c = getch()) == ' ' || c == '\t') {
    ;
  }
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']'; ) {
      ;
    }
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); ) {
      *p++ = c;
    }
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else {
    return tokentype = c;
  }
}

int nexttoken(void) {
  int type;
  type = gettoken();
  prevtoken = YES;
  return type;
}

void dirdcl(void) {
  if (iserror == ERROR) {
    return;
  }
  int type;

  if (tokentype == '(') {
    dcl();
    if (tokentype != ')') {
      // printf("error: missing )\n");
      error("missing )");
      return;
    }
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else {
    // printf("error: expected name or (dcl)\n");
    error("expected name or (dcl)");
    return;
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

void dcl(void) {
  if (iserror == ERROR) {
    return;
  }
  int ns;

  for (ns = 0; gettoken() == '*'; ) {
    ns++;
  }
  dirdcl();
  while (ns-- > 0) {
    strcat(out, " pointer to");
  }
}

int dcl_main(void) {
  iserror = NORMAL;
  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n') {
      // printf("syntax error\n");
      error("syntax error");
    }
    if (iserror == NORMAL) {
      printf("%s: %s %s\n", name, out, datatype);
    } else {
      return -1;
    }
  }
  return 0;
}

int undcl(void) {
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
        strcat(out, token);
      } else if (type == '*') {
        if ((type = nexttoken()) == PARENS || type == BRACKETS) {
          sprintf(temp, "(*%s)", out);
        } else {
          sprintf(temp, "*%s", out);
        }
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else {
        printf("invalid input at %s\n", token);
        return -1;
      }
    }
    printf("%s\n", out);
  }
  return 0;
}

// Exercise 5-18
void error(char* message) {
  printf("Error: %s\n", message);
  tokentype = -1;
  token[0] = '\0';
  name[0] = '\0';
  datatype[0] = '\0';
  out[0] = '\0';
  clear_getchbuff();
  iserror = ERROR;
}