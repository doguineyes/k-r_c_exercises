/*
  Exercise 6-2 Write a program that reads a C program and prints in alphabetical order each
  group of variable names that are identical in the first 6 characters. but different
  somewhere there after. Don't count words within strings and comments. Make
  6 a parameter that can be set from the command line.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "exercise6_1.h" // getword
#include "getch.h"

#define MAXWORD 100
#define DEFAULTNUM 6
#define YES 1
#define NO 0

struct tnode {
  char* word;
  int match;
  struct tnode* left;
  struct tnode* right;
};

struct tnode* talloc(void) {
  return (struct tnode*) malloc(sizeof(struct tnode));
}

char* strdup_my(char* s) {
  char* p;

  p = (char*) malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

void treexprint(struct tnode *p) {
  if (p != NULL) {
    treexprint(p->left);
    if (p->match == YES) {
      printf("%s\n", p->word);
    }
    treexprint(p->right);
  }
}

int compare(char*, struct tnode*, int, int*);

struct tnode* addtreex(struct tnode* p, char* w, int num, int* found) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup_my(w);
    p->match = *found;
    p->left = NULL;
    p->right = NULL;
  } else if ((cond = compare(w, p, num, found)) > 0) {
    p->right = addtreex(p->right, w, num, found);
  } else if (cond < 0) {
    p->left = addtreex(p->left, w, num, found);
  } 
  // else {
  //   p->match = YES;
  //   *found = YES;
  // }

  return p;
}

int compare(char* s, struct tnode* p, int num, int* found) {
  int i;
  char *t = p->word;

  for (i = 0; *s == *t; i++, s++, t++) {
    if (*s == '\0') {
      return 0;
    }
  }
  // printf("w %s, i %d\n", s, i);
  if (i >= num) {
    // printf("found %s at %d\n", s, p);
    *found = YES;
    p->match = YES;
  }
  return *s - *t;
}

int treex_main(int argc, char* argv[]) {
  char word[MAXWORD];
  struct tnode* root = NULL;
  int found = NO;

  int num = (argc == 2 && argv[1][0] == '-') ? atoi(argv[1] + 1) : DEFAULTNUM;

  // printf("num is %d\n", num);

  while(getword(word, MAXWORD) != EOF) {
    // printf("word: %s\n", word);
    if (isalpha(word[0]) && strlen(word) >= num) {
      // printf("word: %s\n", word);
      root = addtreex(root, word, num, &found);
      found = NO;
    }
  }

  treexprint(root);
  return 0;
}

int main(void) {
  char s1[] = "hello helcc helww 123 workk your world wordd heljj workk heljj";
  ungetch(EOF);
  ungets(s1);

  int argc = 2;
  char argv0[] = "treex";
  char argv1[] = "-3";
  char* argv[] = { argv0, argv1 };
  treex_main(argc, argv);
}