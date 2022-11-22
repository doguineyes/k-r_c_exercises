/*
  Exercise 5-7 Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?
*/
#include <string.h>
#include <stdio.h>
#define MAXSTORAGE 50000
#define MAXLEN 1000

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

void writelines(char *lineptr[], int nlines) {
  for (int i = 0; i < nlines; i++) {
    printf("%s\n", lineptr[i]);
  }
}

int main() {
  const int maxlines = 50;
  char storage [MAXSTORAGE];
  char *lineptr[maxlines];
  int nlines = readlines(lineptr, storage, maxlines);
  writelines(lineptr, nlines);
}