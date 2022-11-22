/*
  Exercise 5-9 Rewrite the routines day_of_year and month_day with pointers instead of indexing.
*/
#include <assert.h>
#include <stdio.h>

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day) {
  if (month < 1 || month > 12 || day < 1 || day > 31) {
    return -1;
  }
  int i, leap;
  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  if (day > *(*(daytab + leap) + month)) {
    return -1;
  }
  char *p = *(daytab + leap);
  for (i = 1; i < month; i++) {
    day += *(p + i);
  }
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  int total = leap == 0 ? 365 : 366;
  if (yearday < 1 || yearday > total) {
    *pmonth = -1;
    *pday = -1;
    return;
  }
  char *p = *(daytab + leap);
  for (i = 1; yearday > *(p + i); i++) {
    yearday -= *(p + i);
  }
  *pmonth = i;
  *pday = yearday;
}

int main() {
  assert(day_of_year(2022, 1, 1) == 1);
  assert(day_of_year(2022, 1, 2) == 2);
  assert(day_of_year(2022, 2, 29) == -1);
  assert(day_of_year(2022, 4, 31) == -1);
  assert(day_of_year(2022, 4, 30) == 120);
  assert(day_of_year(2022, 12, 31) == 365);
  assert(day_of_year(2000, 2, 29) == 60);
  assert(day_of_year(2000, 4, 30) == 121);
  assert(day_of_year(2000, 12, 31) == 366);

  int month = 0;
  int day = 0;
  month_day(2000, day_of_year(2000, 3, 17), &month, &day);
  assert(month == 3);
  assert(day == 17);

  month_day(2022, 366, &month, &day);
  assert(month == -1);
  assert(day == -1);
}