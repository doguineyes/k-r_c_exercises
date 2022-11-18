#include <stdio.h>

#define IN_QUOTE 1
#define OUT_QUOTE 0
#define IN_COMMENT_TYPE_ONE 1
#define IN_COMMENT_TYPE_TWO 2
#define OUT_COMMENT 0

char s[] = "/*  */";

int main() {
  char prevChar = '\0';
  char c;
  int quote = OUT_QUOTE;
  int comment = OUT_COMMENT;
  while((c = getchar()) != EOF) {
    if (c == '"') {
      if (quote == OUT_QUOTE) {
        quote = IN_QUOTE;
      } else {
        quote = OUT_QUOTE;
      }
    } else if (c == '/') {
      if (prevChar == '*') {
      }
    }
  }
}