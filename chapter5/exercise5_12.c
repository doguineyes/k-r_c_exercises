/*
  Exercise 5-12 
  Extend en tab and de t a b to accept the shorthand
    entab -m +n
  to mean tab stops every n columns, starting at column m.
  Choose convenient (for the user) default behavior.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MAXLINE 100
#define TABINC 8
#define YES 1
#define NO 0

int get_m_n(int argc, char* argv[], int *m, int *n) {
  if (argc != 3) {
    return -1;
  }
  *m = -1;
  *n = -1;
  char *p;
  for (int i = 1; i <= 2; i++) {
    if (argv[i][0] == '-') {
      p = argv[i];
      // *m = abs(atoi(p));
      *m = atoi(p+1);
    } else if (argv[i][0] == '+') {
      p = argv[i];
      *n = atoi(p+1);
    }
  }
  if (*m < 0 || *n < 0) {
    return -1;
  }
  return 0;
}

void settab(int argc, char* argv[], char* tab) {
  tab[0] = NO;
  // Exercise 5-12
  int m = -1;
  int n = -1;
  if (argc == 3 && get_m_n(argc, argv, &m, &n) == 0) {
    for (int i = 1; i <= MAXLINE; i++) {
      if (i >= m && i % n == 0) {
        tab[i] = YES;
      } else {
        tab[i] = NO;
      }
    }
    return;
  }

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

int main(int argc, char* argv[]) {
  char tab[MAXLINE+1];
  settab(argc, argv, tab);
  for (int i = 1; i <= MAXLINE; i++) {
    printf("%d",tab[i]);
  }
}