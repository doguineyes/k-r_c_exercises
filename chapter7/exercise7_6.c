/*
  Exercise 7-6 Write a program to compare two files. printing the first line where they differ.
*/
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int printfirdiff(char* f1, char* f2) {
  FILE* fp1;
  FILE* fp2;
  if ((fp1 = fopen(f1, "r")) == NULL || (fp2 = fopen(f2, "r")) == NULL) {
    printf("can not open file\n");
    return -1;
  }
  char line1[MAXLINE];
  char line2[MAXLINE];
  char* r1 = NULL;
  char* r2 = NULL;
  for (r1 = fgets(line1, MAXLINE, fp1), r2 = fgets(line2, MAXLINE, fp2); r1 != NULL && r2 != NULL; r1 = fgets(line1, MAXLINE, fp1), r2 = fgets(line2, MAXLINE, fp2)) {
    if (strcmp(line1, line2) != 0) {
      printf("line1: %s\n=====\nline2: %s\n", line1, line2);
      return 1;
    }
  }
  if (r1 == NULL && r2 == NULL) {
    return 0;
  }
  if (r1 == NULL) {
    printf("line1: NULL\n=====\nline2: %s\n", line2);
  } else {
    printf("line1: %s\n=====\nline2: NULL\n", line1);
  }
  return 1;
}

int main() {
  printfirdiff("./exercise7_6_test1", "./exercise7_6_test2");
}