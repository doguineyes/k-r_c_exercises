/*
  Exercise 4-13 Write a recursive version of the function reverse(s), which reverses the string s in place.
*/
#include <string.h>
#include <assert.h>

void reverse_r(char s[], int first, int last) {
  if (first >= last) {
    return;
  } else {
    char c = s[first];
    s[first] = s[last];
    s[last] = c;
    reverse_r(s, first+1, last-1);
  }
}

void reverse(char s[]){
  reverse_r(s, 0, strlen(s)-1);
}

int main() {
  char s[] = "hello world!";
  reverse(s);
  assert(strcmp(s, "!dlrow olleh") == 0);

  char s1[] = "h";
  reverse(s1);
  assert(strcmp(s1, "h") == 0);

  char s2[] = "";
  reverse(s2);
  assert(strcmp(s2, "") == 0);
}