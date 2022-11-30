/*
  Exercise 6-5 Write a cross-referencer that prints a list of all words in a document.
  and for each word, a list of the line numbers on which it occurs.
  Remove noise words like "the," "and." and so on.
*/
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define HASHSIZE 2

struct nlist {
  struct nlist* next;
  char* name;
  char* defn;
};

static struct nlist* hashtab[HASHSIZE];

unsigned hash(char* s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

char* strdup_my(char* s) {
  char* p;
  p = (char*) malloc(sizeof(strlen(s) + 1));
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

struct nlist* lookup(char* s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np;
    }
  }
  return NULL;
}

struct nlist* install(char* name, char* defn) {
  struct nlist* np;
  unsigned hashval;

  if((np = lookup(name)) == NULL) {
    np = (struct nlist*) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup_my(name)) == NULL) {
      return NULL;
    }
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free((void *) np->defn);
  }
  if ((np->defn = strdup_my(defn)) == NULL) {
    return NULL;
  }
  return np;
}

void undef(char* name, char* defn) {
  struct nlist* np = NULL;
  struct nlist* prev = NULL;

  for (np = hashtab[hash(name)]; np != NULL; prev = np, np = np->next) {
    if (strcmp(np->name, name) == 0 && strcmp(np->defn, defn) == 0) {
      if (prev == NULL) {
        hashtab[hash(name)] = np -> next;
      } else {
        prev->next = np->next;
      }
      free((void*) np->name);
      free((void*) np->defn);
      free((void*) np);
    }
  }
}

void nlistprint() {
  struct nlist* np;

  for (int i = 0; i < HASHSIZE; i++) {
    if (hashtab[i] != NULL) {
      printf("%d:", i);
    }
    for (np = hashtab[i]; np != NULL; np = np->next) {
      printf("%s -> %s, ", np -> name, np -> defn);
    }
    if (hashtab[i] != NULL) {
      printf("\n");
    }
  }
}

int main() {
  install("hello", "1");
  install("world", "2");
  install("odd", "3");
  install("bug", "4");
  nlistprint();
  assert(strcmp(lookup("hello")->defn, "1") == 0);

  undef("bug", "4");
  assert(lookup("odd") != NULL);
  assert(lookup("world") != NULL);
  assert(lookup("bug") == NULL);
  assert(lookup("hello") != NULL);
  nlistprint();

  undef("odd", "3");
  assert(lookup("odd") == NULL);
  assert(lookup("world") != NULL);
  assert(lookup("bug") == NULL);
  assert(lookup("hello") != NULL);
  nlistprint();

  install("bug", "4");
  install("odd", "3");
  nlistprint();
  undef("world", "2");
  assert(lookup("odd") != NULL);
  assert(lookup("world") == NULL);
  assert(lookup("bug") != NULL);
  assert(lookup("hello") != NULL);
  nlistprint();
  undef("hello", "1");
  assert(lookup("odd") != NULL);
  assert(lookup("world") == NULL);
  assert(lookup("bug") != NULL);
  assert(lookup("hello") == NULL);
  nlistprint();
}