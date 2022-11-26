/*
  Exercise 5-14 Modify the sort program to handle a -r flag,
  which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.

  Exercise 5-15 Add the option -f to fold upperand lower case together,
  so that case distinctions are not made during sorting; for example, a and A compare equal.

  Exercise 5-16 Add the -d ("directory order") option, which makes comparisons only on let­ters, numbers, and blanks.
  Make sure it works in conjunction with -f .
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define MAXLINES 5000
#define MAXSTORAGE 500000
#define MAXLEN 100
char* lineptr[MAXLINES];

static int pos1 = -1;
static int pos2 = -1;

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

void substr(char* s, char* t) {
  int len = strlen(s);
  if (pos1 >= len) {
    t[0] = '\0';
    return;
  }
  int start = pos1;
  int end;
  if (pos2 >= len) {
    end = len-1;
  } else {
    end = pos2;
  }
  int i, j;
  for (i = start, j=0; i <= end; i++, j++) {
    t[j] = s[i];
  }
  t[j] = '\0';
}

int numcmp(char* s1, char* s2) {
  double v1, v2;
  char s[MAXLEN];

  //Exercise 5-17
  if (pos1 < 0 || pos2 < 0) {
    v1 = atof(s1);
    v2 = atof(s2);
  } else {
    substr(s1, s);
    v1 = atof(s);
    substr(s2, s);
    v2 = atof(s);
  }
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

/*
  Exercise 5-15
*/
int strcmp_i(char* s1, char* s2) {
  int i;
  char c1, c2;
  for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
    c1 = tolower(s1[i]);
    c2 = tolower(s2[i]);
    if (c1 > c2) {
      return i;
    } else if (c1 < c2) {
      return -i;
    }
  }
  c1 = tolower(s1[i]);
  c2 = tolower(s2[i]);
  if (c1 > c2) {
    return i;
  } else if (c1 < c2) {
    return -i;
  } else {
    return 0;
  }
}

int strcmp_i_ans(char* s1_o, char* s2_o) {
  //Exercise 5-17
  char s1_b[MAXLEN], s2_b[MAXLEN];
  char *s1, *s2;
  if (pos1 < 0 || pos2 < 0) {
    s1 = s1_o;
    s2 = s2_o;
  } else {
    substr(s1_o, s1_b);
    s1 = s1_b;
    substr(s2_o, s2_b);
    s2 = s2_b;
  }

  for(; tolower(*s1) == tolower(*s2); s1++, s2++) {
    if (*s1 == '\0') {
      return 0;
    }
  }
  return tolower(*s1) - tolower(*s2);
}

//Exercise 5-17
int strcmp_my(char *s1_o, char *s2_o) {
  char s1_b[MAXLEN], s2_b[MAXLEN];
  char *s1, *s2;
  if (pos1 < 0 || pos2 < 0) {
    s1 = s1_o;
    s2 = s2_o;
  } else {
    substr(s1_o, s1_b);
    s1 = s1_b;
    substr(s2_o, s2_b);
    s2 = s2_b;
  }

  for(; *s1 == *s2; s1++, s2++) {
    if (*s1 == '\0') {
      return 0;
    }
  }
  return *s1 - *s2;
}

//Exercise 5-16
int dircmp(char *s_o, char *t_o) {
  //Exercise 5-17
  char s_b[MAXLEN], t_b[MAXLEN];
  char *s, *t;
  if (pos1 < 0 || pos2 < 0) {
    s = s_o;
    t = t_o;
  } else {
    substr(s_o, s_b);
    s = s_b;
    substr(t_o, t_b);
    t = t_b;
  }

  char a, b;
  do {
    while (!isalnum(*s) && *s != ' ' && *s != '\0') {
      s++;
    }
    while (!isalnum(*t) && *t != ' ' && *t != '\0') {
      t++;
    }
    a = *s;
    s++;
    b = *t;
    t++;
    if (a == b && a == '\0') {
      return 0;
    }
  } while (a == b);
  return a - b;
}

int dircmp_i(char *s_o, char *t_o) {
  char s_b[MAXLEN], t_b[MAXLEN];
  char *s, *t;
  if (pos1 < 0 || pos2 < 0) {
    s = s_o;
    t = t_o;
  } else {
    substr(s_o, s_b);
    s = s_b;
    substr(t_o, t_b);
    t = t_b;
  }

  char a, b;
  do {
    while (!isalnum(*s) && *s != ' ' && *s != '\0') {
      s++;
    }
    while (!isalnum(*t) && *t != ' ' && *t != '\0') {
      t++;
    }
    a = tolower(*s);
    s++;
    b = tolower(*t);
    t++;
    if (a == b && a == '\0') {
      return 0;
    }
  } while (a == b);
  return a - b;
}

int main(int argc, char* argv[]) {
  // assert(strcmp_i("hello", "HELLO") == 0);
  // assert(strcmp_i("hello", "Hello") == 0);
  // assert(strcmp_i("Hello", "helloa") < 0);
  // assert(strcmp_i("helloA", "Hello") > 0);

  int nlines;
  int numeric = 0;
  int r = 1;
  int ignore = 0;
  int direction = 0;
  int field_start = 0;
  int field_end = 0;
  char storage [MAXSTORAGE];

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp("-n", argv[i]) == 0) {
        numeric = 1;
      } else if (strcmp("-r", argv[i]) == 0) {
        r = -1;
      } else if (strcmp("-f", argv[i]) == 0) {
        ignore = 1;
      } else if (strcmp("-d", argv[i]) == 0) {
        direction = 1;
      } else if (argv[i][0] == '+') {
        pos1 = atoi(argv[i] + 1);
      } else if (argv[i][0] == '-') {
        pos2 = atoi(argv[i] + 1);
      }
    }
    if (pos1 > pos2) {
      printf("Usage: sort -r -n -d [+pos1] [-pos2]");
      return -1;
    }
  }
  if ((nlines = readlines(lineptr, storage, MAXLINES)) >= 0) {
    int (*f) (void*, void*) = NULL;
    if (numeric) {
      f = (int (*)(void*, void*))numcmp;
    } else if (direction) {
      if (ignore) {
        f = (int (*)(void*, void*))dircmp_i;
      } else {
        f = (int (*)(void*, void*))dircmp;
      }
    } else {
      if (ignore) {
        f = (int (*)(void*, void*))strcmp_i_ans;
      } else {
        f = (int (*)(void*, void*))strcmp_my;
      }
    }
    qsort_my((void **) lineptr, 0, nlines-1, 
      // (int (*)(void*, void*))(numeric ? numcmp : (ignore ? strcmp_i_ans : strcmp)), r);
      f, r);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}