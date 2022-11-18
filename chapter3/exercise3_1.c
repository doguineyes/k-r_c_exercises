/*
  Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside).
  Write a version with only one test inside the loop and measure the difference in run-time.
*/
#include <assert.h>

/*
  This is the answer given in the answer book.
  I think there is still going to be three tests per loop here, with no noticeable reduction in runtime.
  I don't know how to do less than three tests in each loop, so that when x=v[mid] it will be stuck in an infinite loop.
*/
/* Search x in v[0] <= v[1] <= v[2] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
  int low = 0;
  int high = n - 1;
  int mid = (low + high) / 2;
  while (low <= high && x != v[mid]) {
    if (x < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
    mid = (low + high) / 2;
  }
  if (x == v[mid]) {
    return mid;
  } else {
    return -1;
  }
}

int main() {
  int x = 19;
  int v1[] = {5, 7, 7, 8, 19, 21, 199, 299};
  assert(binsearch(x, v1, 8) == 4);

  int v2[] = {5, 7, 7, 8, 21, 21, 199, 299};
  assert(binsearch(x, v2, 8) == -1);

  int v3[] = {5, 19};
  assert(binsearch(x, v3, 2) == 1);

  int v4[] = {19, 19999};
  assert(binsearch(x, v4, 2) == 0);

  int v5[] = {19};
  assert(binsearch(x, v5, 1) == 0);

  int v6[] = {1999};
  assert(binsearch(x, v6, 1) == -1);
}