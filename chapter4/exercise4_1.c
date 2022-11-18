/*
  Write the function strrindex(s, t), which returns the position of
  the right most occurrence of t in s, or -1 if there is none.
*/
#include <assert.h>
#include <string.h>

int strrindex(char s[], char t[]) {
  int i, j;
  int pos = -1;
  for (i = 0; s[i] != '\0'; i++) {
    if (s[i] == t[0]) {
      for(j = 1; t[j] != '\0' && t[j] == s[i + j]; j++) {
      }
      if (t[j] == '\0') {
        pos = i;
      }
    }
  }
  return pos;
}

int strrindex_fr(char s[], char t[]) {
  int i, j;
  int pos = -1;
  for (i = strlen(s) - strlen(t); i >= 0; i--) {
    for (j = 0; t[j] != '\0' && s[i + j] == t[j]; j++) {
    }
    if (j > 0 && t[j] == '\0') {
      pos = i;
      break;
    }
  }
  return pos;
}

int main() {
  char s1[] = "www";
  char t1[] = "ww";
  assert(strrindex(s1, t1) == 1);
  assert(strrindex_fr(s1, t1) == 1);

  char s2[] = "hello world hello c!";
  char t2[] = "hellow";
  assert(strrindex(s2, t2) == -1);
  assert(strrindex_fr(s2, t2) == -1);

  char t3[] = "hello";
  assert(strrindex(s2, t3) == 12);
  assert(strrindex_fr(s2, t3) == 12);

  char t4[] = "";
  assert(strrindex(s2, t4) == -1);
  assert(strrindex_fr(s2, t4) == -1);

  char s3[] = "";
  assert(strrindex(s3, t2) == -1);
  assert(strrindex_fr(s3, t2) == -1);
  assert(strrindex(s3, t4) == -1);
  assert(strrindex_fr(s3, t4) == -1);
}