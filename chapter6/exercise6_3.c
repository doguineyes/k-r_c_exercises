/*
  Exercise 6-3 Write a cross-referencer that prints a list of all words in a document.
  and for each word, a list of the line numbers on which it occurs.
  Remove noise words like "the," "and." and so on.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "exercise6_1.h" // getword

#define MAXWORD 100
#define YES 1
#define NO 0

struct pagenode {
  int pagenum;
  struct pagenode* next;
};

struct pagenode* pnodealloc(void) {
  return (struct pagenode*) malloc(sizeof(struct pagenode));
}

struct pagenode* newpagelist(int pagenum) {
  struct pagenode* p = pnodealloc();
  p->pagenum = pagenum;
  p->next = NULL;
  return p;
}

struct pagenode* addpnodetail(struct pagenode* tail, int pagenum) {
  struct pagenode* p = newpagelist(pagenum);
  tail->next = p;
  return p;
}

void pnodelistprint(struct pagenode* head) {
  struct pagenode* p = head;
  while (p != NULL) {
    printf("%d, ", p->pagenum);
    p = p->next;
  }
}

struct ptreenode {
  char* word;
  struct pagenode* head;
  struct pagenode* tail;
  struct ptreenode* left;
  struct ptreenode* right;
};

struct ptreenode* talloc(void) {
  return (struct ptreenode*) malloc(sizeof(struct ptreenode));
}

char* strdup_my(char* s) {
  char* p;

  p = (char*) malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

struct ptreenode*
addptreenode(struct ptreenode* p, char* word, int pagenum) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup_my(word);
    p->head = newpagelist(pagenum);
    p->tail = p->head;
    p->left = NULL;
    p->right = NULL;
  } else if ((cond = strcmp(word, p->word)) == 0) {
    if (pagenum > p->tail->pagenum) {
      p->tail = addpnodetail(p->tail, pagenum);
    }
  } else if (cond < 0) {
    p->left = addptreenode(p->left, word, pagenum);
  } else if (cond > 0) {
    p->right = addptreenode(p->right, word, pagenum);
  }

  return p;
}

void ptreeprint(struct ptreenode* root) {
  if (root != NULL) {
    ptreeprint(root -> left);
    printf("%s: ", root -> word);
    pnodelistprint(root -> head);
    printf("\n");
    ptreeprint(root -> right);
  }
}

int isstopword(char* w) {
  if (strcmp(w, "the") == 0 || strcmp(w, "and") == 0 || strcmp(w, "a") == 0 || strcmp(w, "an") == 0) {
    return YES;
  }
  return NO;
}

int lineindex(void) {
  char word[MAXWORD];
  int linenum = 1;
  int c;
  struct ptreenode* root = NULL;

  while ((c = getword(word, MAXWORD)) != EOF) {
    if (c == '\n') {
      linenum++;
    } else if (isalpha(word[0]) && isstopword(word) != YES) {
      root = addptreenode(root, word, linenum);
    }
  }
  ptreeprint(root);
  return 0;
}