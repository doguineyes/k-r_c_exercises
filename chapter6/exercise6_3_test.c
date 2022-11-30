#include <assert.h>
#include <stdio.h>
#include "exercise6_3_test.h"
#include "getch.h"

int main(void) {
  char s1[] = "hello helcc helww 123 workk the a \nyour world wordd heljj workk heljj\n them and your my world hello\n your12 my12 world an hello";
  ungetch(EOF);
  ungets(s1);

  lineindex();
}