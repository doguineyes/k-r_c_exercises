/*
  Extend atof to handle scientific notation of the form
  123.45e-6
  where a floating-point number maybe followed by e or E and a n optionally signed exponent.
*/
#include <ctype.h>
#include <math.h>
#include <assert.h>

double atof(char s[]) {
  double val, power;
  int i, sign;
  for (i = 0; isspace(s[i]); i++) {
    ;
  }
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }
  for (val = 0.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i] == '.') {
    i++;
  }
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }
  if (s[i] == 'e' || s[i] == 'E') {
    i++;
    int esign;
    int epower;
    esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
      i++;
    }
    for (epower = 0; isdigit(s[i]); i++) {
      epower = 10 * epower + (s[i] - '0');
    }
    epower = esign * epower;
    power /= pow(10.0, epower);
  }
  return sign * val / power;
}

int main() {
  assert(atof("13.13") == 13.13);
  assert(atof("-0.013") == -0.013);
  assert(atof("0") == 0.0);
  assert(atof("13331") == 13331.0);
  assert(atof("-13331.0") == -13331.0);
  assert(atof("123.45e-6") == 0.00012345);
  assert(atof("123.45e6") == 123450000.0);
  assert(atof("123.45e1") == 1234.5);
  assert(atof("123.45e-1") == 12.345);
  assert(atof("123.45E0") == 123.45);
  assert(atof("123.45E-0") == 123.45);
}