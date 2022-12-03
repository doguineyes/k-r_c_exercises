/*
  Exercise 7-7 Modify the pattern-finding program of Chapter 5 to take its input from a set of named files or,
  if no files are named as arguments. from the standard input. Should the file name be printed when a matching line is found?
*/
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int find(FILE* fp, char* pattern, char* linebuf, int maxline, char* filename) {
  while (fgets(linebuf, maxline, fp) != NULL) {
    if (strstr(linebuf, pattern) != NULL) {
      printf("%s: %s\n", filename, linebuf);
      break;
    }
  }
  fclose(fp);
  return 0;
}

int patternfiles(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: patternfiles pattern [files...]\n");
    return -1;
  }
  char* pattern = argv[1];
  char linebuf[MAXLINE];
  char* filename;
  FILE* fp = NULL;

  if (argc == 2) {
    find(stdin, pattern, linebuf, MAXLINE, "stdin");
    return 0;
  }

  int i;

  for (i = 2; i < argc; i++) {
    filename = argv[i];
    if((fp = fopen(filename, "r")) == NULL) {
      printf("Can not open file %s\n", filename);
      return -2;
    }
    find(fp, pattern, linebuf, MAXLINE, filename);
  }

  return 0;
}

int main(int argc, char* argv[]) {
  patternfiles(argc, argv);
}