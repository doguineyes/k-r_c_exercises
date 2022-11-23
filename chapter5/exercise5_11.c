/*
  Exercise 5-11 Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments.
  Use the default tab settings if there are no arguments.
*/
#include <stdlib.h>
#include <stdio.h>
#define MAXLINE 100
#define TABINC 8
#define YES 1
#define NO 0

void settab(int argc, char* argv[], char* tab) {
  tab[0] = NO;
  if (argc <= 1) {
    for (int i = 1; i <= MAXLINE; i++) {
      if (i % TABINC == 0) {
        tab[i] = YES;
      } else {
        tab[i] = NO;
      }
    }
  } else {
    for (int i = 1; i <= MAXLINE; i++) {
      tab[i] = NO;
    }
    for (int i = 1; i < argc; i++) {
      tab[atoi(argv[i])] = YES;
    }
  }
}

int tabpos(int pos, char* tab) {
  if (pos > MAXLINE) {
    return YES;
  } else {
    return tab[pos];
  }
}

void detab(char* tab) {
  int c;
  int pos = 1;
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      do {
        putchar(' ');
      } while (tabpos(pos++, tab) != YES);
    } else if (c == '\n') {
      putchar(c);
      pos = 1;
    } else {
      putchar(c);
      pos++;
    }
  }
}

void entab(char* tab) {
  int c, pos;
  int nb = 0;
  int nt = 0;

  for (pos = 1; (c = getchar()) != EOF; pos++) {
    if (c == ' ') {
      if (tabpos(pos, tab) == NO) {
        ++nb;
      } else {
        nb = 0;
        ++nt;
      }
    } else {
      for ( ; nt > 0; nt--) {
        putchar('\t');
      }
      if (c == '\t') {
        nb = 0;
      } else {
        for ( ; nb > 0; nb--) {
          putchar(' ');
        }
      }
      putchar(c);
      if (c == '\n') {
        pos = 0;
      } else if (c == '\t') {
        while (tabpos(pos, tab) != YES) {
          ++pos;
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  char tab[MAXLINE+1];
  settab(argc, argv, tab);
  // for (int i = 1; i <= MAXLINE; i++) {
  //   printf("%d",tab[i]);
  // }
  // detab(tab);
  entab(tab);
  return 0;
}