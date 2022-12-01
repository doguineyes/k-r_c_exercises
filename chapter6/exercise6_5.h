struct nlist {
  struct nlist* next;
  char* name;
  char* defn;
};

struct nlist* lookup(char*);
struct nlist* install(char*, char*);
void undef(char*, char*);
void nlistprint();