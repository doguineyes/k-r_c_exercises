#include <ctype.h>
#include <stdio.h>

int skipcomment(void) {
  int getch(void);
  void ungetch(int);
  int c;
  while((c = getch()) != EOF) {
    if (c == '*') {
      if ((c = getch()) != '/') {
        ungetch(c);
      } else {
        break;
      }
    }
  }
  return c;
}

int getword(char* word, int lim) {
  int getch(void);
  void ungetch(int);
  int c, next;
  char* w = word;

  //getword can catch '\n'
  while(isspace(c = getch()) && c != '\n') {
    ;
  }

  if (c != EOF) {
    *w++ = c;
  }
  if (isalpha(c) || c == '_' || c == '#') {
    for ( ; --lim > 0; w++) {
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
    }
  } else if (c == '\'' || c == '"') {
    for ( ; --lim > 0; w++) {
      if ((*w = getch()) == '\\') {
        *++w = getch();
      } else if (*w == c) {
        w++;
        break;
      } else if (*w == EOF) {
        break;
      }
    }
  } else if (c == '/') {
    if ((next = getch()) == '*') {
      c = skipcomment();
    } else {
      ungetch(next);
    }
  }
  *w = '\0';
  return c;
}