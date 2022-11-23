/*
  Exercise 5-13 Write the program tail. which prints the last n lines of its input.
  By default, n is 10, let us say, but it can be changed by an optional argument, so that
    tai1 -n
  prints the last n lines. 
  The program should behave rationally no matter how unreasonable the input or the value of n.
  Write the program so that it makes the best use of available storage;
  lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSTORAGE 500000
#define MAXLEN 1000
#define TAILN 10

/* getline: read a line into s, return length */
int getline_my(char *s, int lim) {
  if (s == NULL || lim <= 0) {
    return 0;
  }
  int c; // must be int, because char maybe can not hold EOF
  char *h = s;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *s++ = c;
  }
  if (c == '\n') {
    *s++ = c;
  }
  *s = '\0';
  return s - h;
}

/*
  Exercise 5-7
*/
int readlines(char *lineptr[], char *linestorage, int maxlines) {
  int len, nlines;
  char line[MAXLEN];
  char *p = linestorage;
  char *linestop = linestorage + MAXSTORAGE;
  nlines = 0;
  while((len = getline_my(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || p + len > linestop) {
      return -1;
    } else {
      line[len-1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len;
    }
  }
  return nlines;
}

void writetail(char *lineptr[], int nlines, int tail_n) {
  if (tail_n < 1) {
    tail_n = TAILN;
  }
  int start = 0;
  if (tail_n < nlines) {
    start = nlines - tail_n;
  }
  for (int i = start; i < nlines; i++) {
    printf("%s\n", lineptr[i]);
  }
}

int main(int argc, char* argv[]) {
  const int maxlines = 100;
  char storage [MAXSTORAGE];
  char *lineptr[maxlines];
  int nlines = readlines(lineptr, storage, maxlines);
  if (argc > 2) {
    printf("Usage: tail -n");
    return -1;
  } else if (argc == 2 && argv[1][0] == '-') {
    int tailn = atoi(argv[1] + 1);
    printf("\ntail n is:\n");
    writetail(lineptr, nlines, tailn);
  } else {
    printf("\ntail n is:\n");
    writetail(lineptr, nlines, TAILN);
  }
  return 0;
}