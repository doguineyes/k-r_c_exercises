/*
  Write a function escape(s, t) that converts characters like newline and tab into visible escape sequences
  like \n and \t as it copies the string t to s. Use a switch.
  Write a function for the other direction as well, converting escape sequences into the real characters.
*/
#include <string.h>
#include <assert.h>
#include <stdio.h>

void escape(char s[], char t[]) {
  int i, j;
  for (i = j = 0; t[i] != '\0'; i++) {
    switch(t[i]) {
      case '\n':
        s[j] = '\\';
        s[j+1] = 'n';
        j += 2;
        break;
      case '\t':
        s[j] = '\\';
        s[j+1] = 't';
        j += 2;
        break;
      default:
        s[j] = t[i];
        j++;
        break;
    }
  }
  s[j] = '\0';
}

void unescape(char s[], char t[]) {
  int i, j;
  for (i = j = 0; t[i] != '\0'; i++) {
    switch(t[i]) {
      case '\\':
        switch(t[i+1]) {
          case 'n':
            s[j] = '\n';
            i++;
            j++;
            break;
          case 't':
            s[j] = '\t';
            i++;
            j++;
            break;
          default:
            s[j] = t[i];
            j++;
            break;
        }
        break;
      default:
        s[j] = t[i];
        j++;
        break;
    }
  }
  s[j] = '\0';
}

int main() {
  char t[] = "hello\tworld!\n";
  char s[50];
  escape(s, t);
  assert(strcmp(s, "hello\\tworld!\\n") == 0);

  char t1[] = "hello\\tworld!\\n\\quit";
  unescape(s, t1);
  assert(strcmp(s, "hello\tworld!\n\\quit") == 0);
}