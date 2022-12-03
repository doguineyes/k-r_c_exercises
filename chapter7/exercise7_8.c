/*
  Exercise 7-8 Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file.
*/
#include <stdio.h>

#define MAXLINE 500
#define PERPAGELINE 10


int printfiles(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Usage printfiles [filename...]\n");
    return -1;
  }

  FILE* fp;
  int linenum;
  int fnum;
  char* filename;
  char line[MAXLINE];

  for (fnum = 1; fnum < argc; fnum++) {
    filename = argv[fnum];
    if ((fp = fopen(filename, "r")) == NULL) {
      printf("can not open file %s\n", filename);
      return -2;
    }
    linenum = 0;
    // printf("====> new page <====\n");
    printf("/*-----* filename: %s *-----*/\n", filename);
    while(fgets(line, MAXLINE, fp) != NULL) {
      printf("%s", line);
      linenum++;
      if (linenum % PERPAGELINE == 0) {
        printf("/*-----* page %d *-----*/\n", (linenum / PERPAGELINE));
      }
    }
    for (int j = PERPAGELINE - (linenum % PERPAGELINE) + 1; j > 0; j--) {
      printf("\n");
    }
    printf("/*-----* page %d *-----*/\n", (linenum / PERPAGELINE)+1);
  }

  return 0;
}

int main(int argc, char* argv[]) {
  printfiles(argc, argv);
}