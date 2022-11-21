/*
  Exercise 5-3 Write a pointer version of the function strcat that we showed in Chapter 2:
  strcat(s, t) copies the string t to the end of s.
*/
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void strcat_e(char* s, char* t) {
  while(*s != '\0') {
    s++;
  }
  while((*s++ = *t++) != '\0') {
  }
}

void strcat_ans(char *s, char*t) {
  while(*s) {
    s++;
  }
  while((*s++ = *t++)) { //warning: using the result of an assignment as a condition without parentheses
    ;
  }
}

int main() {
  char s[100] = "";
  char s1[100] = "";

  strcat_e(s, "");
  strcat_ans(s1, "");
  assert(strcmp(s, "") == 0);
  assert(strcmp(s1, "") == 0);

  strcat_e(s, "hello ");
  strcat_ans(s1, "hello ");
  assert(strcmp(s, "hello ") == 0);
  assert(strcmp(s1, "hello ") == 0);

  strcat_e(s, "world!");
  assert(strcmp(s, "hello world!") == 0);

  strcat_e(s, "");
  assert(strcmp(s, "hello world!") == 0);

  // segmentation fault
  // strcat_e(s, NULL);
  // assert(strcmp(s, "hello world!") == 0);
}