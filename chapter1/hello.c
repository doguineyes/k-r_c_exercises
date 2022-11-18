#include <stdio.h>

#define TRUE 1
#define FALSE 0

double caluCelsius (double f) {
  return (5.0 * (f - 32.0) / 9.0);
}

double caluFahr (double c) {
  return ((c * 9.0 / 5.0) + 32.0);
}

void printFahrToCelsList() {
  double fahr;
  double celsius;
  int lower = 0;
  int upper = 300;
  int step = 20;

  fahr = lower;

  printf("Let's do some temperature conversion\n");

  while ( fahr <= upper ) {
    celsius = caluCelsius(fahr);
    printf("%3.0f\t%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}

void printCelsToFahrList() {
  double fahr;
  double celsius;
  int lower = 0;
  int upper = 300;
  int step = 20;

  celsius = lower;

  printf("Let's do some temperature conversion\n");

  while ( celsius <= upper ) {
    fahr = caluFahr(celsius);
    printf("%3.0f\t%6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}

void printFrom300To0 () {
  double fahr;
  double celsius;
  int lower = 0;
  int upper = 300;
  int step = 20;

  for (fahr = upper; fahr >= lower; fahr = fahr - step) {
    celsius = caluCelsius(fahr);
    printf("%3.0f\t%6.1f\n", fahr, celsius);
  }
}

void printEOF () {
  printf("The value of EOF is:%d\n\n", EOF);
}

void trimSpaces() {
  int c;
  int firstSpace = FALSE;
  while((c = getchar()) != EOF) {
    if (c != ' ') {
      firstSpace = FALSE;
      putchar(c);
    } else {
      if (firstSpace == TRUE) {
        // do nothing
      } else {
        firstSpace = TRUE;
        putchar(c);
      }
    }
  }
}

int main() {
  // printFahrToCelsList();
  // printCelsToFahrList();
  // printFrom300To0();
  // printEOF();
  // trimSpaces();
}
