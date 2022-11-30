#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "exercise6_1.h" // getword
#include "getch.h"

#define MAXWORD 100

struct tnode {
  char* word;
  int count;
  struct tnode* left;
  struct tnode* right;
};

struct tnode* talloc(void) {
  return (struct tnode*) malloc(sizeof(struct tnode));
}

char* strdup_my(char* s) {
  char* p;
  p = (char*) malloc(sizeof(strlen(s) + 1));
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

struct tnode*
addtree(struct tnode* p, char *w) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup_my(w);
    p->count = 1;
    p->left = NULL;
    p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;
  } else if (cond < 0) {
    p->left = addtree(p->left, w);
  } else if (cond > 0) {
    p->right = addtree(p->right, w);
  }

  return p;
}

struct tnode* addsorttree(struct tnode* p, char *w, int count) {
  if (p == NULL) {
    p = talloc();
    p->word = strdup_my(w);
    p->count = count;
    p->left = NULL;
    p->right = NULL;
  } else if (count < p->count) {
    p->left = addsorttree(p->left, w, count);
  } else {
    p->right = addsorttree(p->right, w, count);
  }
  return p;
}

struct tnode*
transtree(struct tnode* s, struct tnode* t) {
  if (s != NULL) {
    t = transtree(s->left, t);
    t = addsorttree(t, s->word, s->count);
    t = transtree(s->right, t);
  }
  return t;
}

void treeprint(struct tnode* p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

int count_main() {
  char word[MAXWORD];
  struct tnode * stat = NULL;
  struct tnode * sort = NULL;

  while(getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      stat = addtree(stat, word);
    }
  }
  sort = transtree(stat, sort);
  treeprint(sort);
  return 0;
}

int main(void) {
  // char s1[] = "hello helcc hello and and and helww 123 workk the a \nyour world wordd heljj workk heljj\n them and your my world hello\n your12 my12 world an hello";
  char s1[] = "hello world you and you and me and";
  ungetch(EOF);
  ungets(s1);

  count_main();
}