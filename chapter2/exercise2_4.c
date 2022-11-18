/*
  Write an alternate version of squeeze(s1, s2) that deletes each character in s1 that matches any character in the string s2.
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bitmap.h"

void squeeze(char s1[], char s2[]) {
  const int charMapBitsCount = getCountOfBins();
  int charBitMap[charMapBitsCount];
  for(int i = 0; i < charMapBitsCount; i++) {
    charBitMap[i] = 0;
  }
  for (int i = 0; s2[i] != '\0'; i++) {
    set(charBitMap, s2[i]);
  }
  int i, j;
  for (i = j = 0; s1[i] != '\0'; i++) {
    if(get(charBitMap, s1[i]) == 0) {
      s1[j++] = s1[i];
    }
  }
  s1[j] = '\0';
}

void squeeze_ans(char s1[], char s2[]) {
  int i, j, k = 0;
  for (i = 0; s1[i] != '\0'; i++) {
    for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++) {
    }
    if (s2[j] == '\0') {
      s1[k++] = s1[i]; 
    }
  }
  s1[k] = '\0';
}

int main() {

  char s1[] = "hello, world! Hello World0?";
  char s2[] = "h!ll0h";
  squeeze(s1, s2);
  printf("After filter s1: %s\n", s1);
  assert(strcmp(s1, "eo, word Heo Word?") == 0);

  char s1_1[] = "hello, world! Hello World0?";
  char s2_1[] = "h!ll0h";
  squeeze_ans(s1_1, s2_1);
  printf("After filter s1_1: %s\n", s1_1);
  assert(strcmp(s1_1, "eo, word Heo Word?") == 0);
}