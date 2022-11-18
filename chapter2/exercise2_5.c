/*
  Write the function any(s1 ,s2), which returns the first location in the string s1 
  where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. 
  (The standard library function strpbrk does the same job but returns a pointer to the location.)
*/
#include <assert.h>
#include <stdio.h>
#include "bitmap.c"

int any(char s1[], char s2[]) {
  const int charMapBitsCount = getCountOfBins();
  int charBitMap[charMapBitsCount];
  for(int i = 0; i < charMapBitsCount; i++) {
    charBitMap[i] = 0;
  }
  for (int i = 0; s2[i] != '\0'; i++) {
    set(charBitMap, s2[i]);
  }
  int i;
  for (i = 0; s1[i] != '\0'; i++) {
    if (get(charBitMap, s1[i]) == 1) {
      return i;
    }
  }
  return -1;
}

int any2(char s1[], char s2[]) {
  int i, j;
  for (i = 0; s1[i] != '\0'; i++) {
    // Ans 1
    // for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
    //   ;
    // if (s2[j] != '\0') {
    //   return i;
    // }

    // Ans 2 more clear
    for (j = 0; s2[j] != '\0'; j++) {
      if (s1[i] == s2[j]) {
        return i;
      }
    } 
  }
  return -1;
}

int main() {
  char s1[] = "hello, world! Hello World0?";
  char s2[] = "&*^&**?!?KJJJ";
  printf("s1 %s, s2 %s, any %d, any2 %d\n", s1, s2, any(s1, s2), any2(s1, s2));
  assert(any(s1, s2) == 12);
  assert(any2(s1, s2) == 12);

  char s2_1[] = "XXXXXJJGGJK**&^^";
  printf("s1 %s, s2_2 %s, any %d, any2 %d\n", s1, s2_1, any(s1, s2_1), any2(s1, s2_1));
  assert(any(s1, s2_1) == -1);
  assert(any2(s1, s2_1) == -1);
}