/*
  Exercise 4-10 An alternate organization uses getline to read an entire input line;
  this makes getch and ungetch unnecessary. Revise the cakulator to use this approach.

  Exercise 4-11 Modify get op so that it doesn't need to use ungetch.
  Hint: use an internal static variable.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"
#define LINE_BUFF_SIZE 200
#define BUFSIZE 100

int getop(char s[]) {
  int i, c, c_next;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (islower(c)) {
    if (islower(c_next = getch())) {
      i = 0;
      do {
        s[++i] = c_next;
      } while (islower(c_next = getch()));
      s[++i] = '\0';
      ungetch(c_next);
      return FUNCTION;
    } else {
      ungetch(c_next);
    }
  }
  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }
  i = 0;
  // handle negative numbers
  if (c == '-') {
    if(isdigit(c_next = getch()) || c_next == '.') { // support .3 is 0.3, or -.3 is -0.3
      s[++i] = c_next;
      c = c_next;
    } else {
      ungetch(c_next);
      return c;
    }
  }
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  s[i] = '\0';
  // Exercise 4-9 change ungetch to be able to get EOF
  // if (c != EOF) {
  ungetch(c);
  // }
  return NUMBER;
}

//Exercise 4-10
int getline_s(char s[], int lim) {
  int c, i;
  i = 0;
  while(--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    s[i++] = c;
  }
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}

//Exercise 4-10
char line[LINE_BUFF_SIZE];
int line_size = 0;
int pos = 0;

//Exercise 4-10
int getword(char s[]) {
  while (1) {
    if (pos >= line_size) {
      line_size = getline_s(line, LINE_BUFF_SIZE);
      if (line_size == 0) {
        return EOF;
      }
      pos = 0;
    }
    // pos < line_size
    while(pos < line_size && (line[pos] == ' ' || line[pos] == '\t')) {
      pos++;
    }
    int i;
    if (pos < line_size) {
      s[0] = line[pos++];
      if (s[0] == '\n') {
        s[1] = '\0';
        return 1;
      }
      i = 1;
      while (pos < line_size && line[pos] != ' ' && line[pos] != '\t' && line[pos] != '\n') {
        s[i++] = line[pos++];
      }
      s[i] = '\0';
      return i;
    }
  }
}

//Exercise 4-10
int is_func(char s[]) {
  if (strlen(s) <= 1)
    return 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (!islower(s[i])) {
      return 0;
    }
  }
  return 1;
}

//Exercise 4-10
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

//Exercise 4-10
int getop_line(char s[]) {
  while (getword(s) != EOF) {
    if (is_func(s)) {
      return FUNCTION;
    } else if (is_num(s)) {
      return NUMBER;
    } else {
      return s[0];
    }
  }
  return EOF;
}

// Exercise 4-11
int getop_static(char s[]) {
  static int buf[BUFSIZE];
  static int bufp = 0;

  int i, c, c_next;
  while ((s[0] = c = ((bufp > 0) ? buf[--bufp] : getchar())) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (islower(c)) {
    if (islower(c_next = ((bufp > 0) ? buf[--bufp] : getchar()))) {
      i = 0;
      do {
        s[++i] = c_next;
      } while (islower(c_next = ((bufp > 0) ? buf[--bufp] : getchar())));
      s[++i] = '\0';
      // ungetch(c_next);
      if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
      } else {
        buf[bufp++] = c_next;
      }
      return FUNCTION;
    } else {
      // ungetch(c_next);
      if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
      } else {
        buf[bufp++] = c_next;
      }
    }
  }
  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }
  i = 0;
  // handle negative numbers
  if (c == '-') {
    if(isdigit(c_next = ((bufp > 0) ? buf[--bufp] : getchar())) || c_next == '.') { // support .3 is 0.3, or -.3 is -0.3
      s[++i] = c_next;
      c = c_next;
    } else {
      // ungetch(c_next);
      if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
      } else {
        buf[bufp++] = c_next;
      }
      return c;
    }
  }
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = ((bufp > 0) ? buf[--bufp] : getchar())))
      ;
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = ((bufp > 0) ? buf[--bufp] : getchar())))
      ;
  }
  s[i] = '\0';
  // Exercise 4-9 change ungetch to be able to get EOF
  // if (c != EOF) {
  // ungetch(c);
  // }
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
  return NUMBER;
}
