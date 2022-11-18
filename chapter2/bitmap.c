#include <limits.h>
#include "bitmap.h"

int getCountOfBins() {
  const int countOfChar = CHAR_MAX - CHAR_MIN + 1;
  const int intBits = sizeof(int) * 8;
  if (countOfChar % intBits == 0) {
    return countOfChar / intBits;
  } else {
    return (countOfChar / intBits) + 1;
  }
}

int getBinIndex(char c) {
  const int intBits = sizeof(int) * 8;
  const int bitIndex = c - CHAR_MIN; // 0 ~ 255
  return bitIndex / intBits; // 0 ~ 7
}

int getBitInBin(char c) {
  const int intBits = sizeof(int) * 8;
  const int bitIndex = c - CHAR_MIN; // 0 ~ 255
  return bitIndex % intBits; // 0 ~ 31
}

void set(int map[], char c) {
  int binIndex = getBinIndex(c); // 0 ~ 7
  int bitIndexInBin = getBitInBin(c); // 0 ~ 31
  map[binIndex] |= (1 << bitIndexInBin);
}

int get(int map[], char c) {
  int binIndex = getBinIndex(c); // 0 ~ 7
  int bitIndexInBin = getBitInBin(c); // 0 ~ 31
  int mask = 1 << bitIndexInBin;
  int res = map[binIndex] & mask;
  if (res == 0) {
    return 0;
  } else {
    return 1;
  }
}