/*
  Write a function expand(s1, s2) that expands short hand notations like a-z in the string s1
  into the equivalent complete list abc...xyz in s2. 
  Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.
  Arrange that a leading or trailing - is taken literally.
*/
#include <ctype.h>
#include <assert.h>
#include <string.h>

int isSeq(char s1[], int i, int (*isFunc)(int)) {
  return ((*isFunc)(s1[i]) && s1[i+1] == '-' && (*isFunc)(s1[i+2]) && s1[i] < s1[i+2]);
}

void expandOne(char s1[], char s2[], int* i, int* j) {
  char c;
  for (c = s1[*i]; c < s1[(*i)+2]; c++) {
    s2[*j] = c;
    (*j)++;
  }
  (*i)++;
}

void expand(char s1[], char s2[]) {
  int i, j;
  for (i = j = 0; s1[i] != '\0'; i++) {
    if (isSeq(s1, i, isdigit)) {
      expandOne(s1, s2, &i, &j);
    } else if (isSeq(s1, i, islower)) {
      expandOne(s1, s2, &i, &j);
    } else if (isSeq(s1, i, isupper)) {
      expandOne(s1, s2, &i, &j);
    } else {
      s2[j] = s1[i];
      j++;
    }
  }
  s2[j] = '\0';
}

void expand_ans(char s1[], char s2[]) {
  char c;
  int i, j;
  i = j = 0;
  while ((c = s1[i++]) != '\0') {
    if (s1[i] == '-' && s1[i+1] >= c) {
      i++;
      while (c < s1[i]) {
        s2[j++] = c++;
      }
    } else {
      s2[j++] = c;
    }
  }
  s2[j] = '\0';
}

int main() {
  char s1[] = "hello a- - - e-h0-9 world a-d-g,; X-Z";
  char s2[100];
  expand(s1, s2);
  assert(strcmp(s2, "hello a- - - efgh0123456789 world abcdefg,; XYZ") == 0);

  char s12[] = "hello a-b-c world";
  expand(s12, s2);
  assert(strcmp(s2, "hello abc world") == 0);
  expand_ans(s12, s2);
  assert(strcmp(s2, "hello abc world") == 0);
}