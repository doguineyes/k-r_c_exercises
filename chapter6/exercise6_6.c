#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "exercise6_1.h" //getword
#include "getch.h"
#include "exercise6_5.h"

#define MAXWORD 100

void out(char* w) {
  printf("%s ", w);
}

int handledefine() {
  char word[MAXWORD];
  char c;
  char name[MAXWORD];
  char defn[MAXWORD];
  struct nlist* p = NULL;

  while((c = getword(word, MAXWORD)) != EOF) {
    if (c == '#' && strcmp(word, "#define") == 0) {
      if (isalnum(getword(name, MAXWORD)) && isalnum(getword(defn, MAXWORD))) {
        // printf("add name %s defn %s\n", name, defn);
        if(install(name, defn) == NULL) {
          printf("error: install name defn return null\n");
          return -1;
        }
      }
      out(word);
      out(name);
      out(defn);
    } else if (isalpha(c)) {
      if ((p = lookup(word)) != NULL) {
        out(p->defn);
      } else {
        out(word);
      }
    } else {
      out(word);
    }
  }

  return 0;
}

int main() {
  char s[] = "#define N 100\n#define MAXWORD hellow\nint i = N;\nMAXWORD ();\n";
  char word[MAXWORD];
  char c;

  ungetch(EOF);
  ungets(s);

  handledefine();
}