#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "exercise6_1.h"
#include "getch.h"

int main(void) {
  char s[] = "hello world\n";
  ungetch(EOF);
  ungets(s);

  char word[MAXWORD+1];
  getword(word, MAXWORD);
  assert(strcmp(word, "hello") == 0);

  getword(word, MAXWORD);
  assert(strcmp(word, "world") == 0);

  assert(getword(word, MAXWORD) == EOF);
  assert(strcmp(word, "") == 0);

  clearbuf();
  for (int i = 0; i < MAXWORD + 50; i++) {
    ungetch('a');
  }
  getword(word, MAXWORD);
  assert(strlen(word) == MAXWORD);

  clearbuf();
  char s1[] = "hello_WORD #hello /* hello123 123 word */ \"your word\"\n";
  ungetch(EOF);
  ungets(s1);
  
  getword(word, MAXWORD);
  assert(strcmp(word, "hello_WORD") == 0);

  getword(word, MAXWORD);
  assert(strcmp(word, "#hello") == 0);

  assert(getword(word, MAXWORD) == '/');
  
  getword(word, MAXWORD);
  assert(strcmp(word, "\"your word\"") == 0);
}