/*
  Exercise 5-14 Modify the sort program to handle a -r flag,
  which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINES 5000
#define MAXSTORAGE 500000
#define MAXLEN 100
char* lineptr[MAXLINES];

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

void qsort_my(void* v[], int left, int right, int (*comp) (void *, void *), int r) {
  int i, last;
  void swap(void* v[], int, int);
  r = r < 0 ? -1 : 1;

  if (left >= right) {
    return;
  }
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (r * (*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort_my(v, left, last - 1, comp, r);
  qsort_my(v, last + 1, right, comp, r);
}

void swap(void *v[], int i, int j) {
  void* temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int numcmp(char* s1, char* s2) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char* argv[]) {
  int nlines;
  int numeric = 0;
  int r = 1;
  char storage [MAXSTORAGE];

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp("-n", argv[i]) == 0) {
        numeric = 1;
      } else if (strcmp("-r", argv[i]) == 0) {
        r = -1;
      }
    }
  }
  if ((nlines = readlines(lineptr, storage, MAXLINES)) >= 0) {
    qsort_my((void **) lineptr, 0, nlines-1, 
      (int (*)(void*, void*))(numeric ? numcmp : strcmp), r);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}