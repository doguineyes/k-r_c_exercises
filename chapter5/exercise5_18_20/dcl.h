enum { NAME, PARENS, BRACKETS };
int getch(void);
void ungetch(int);
void clear_getchbuff(void);
void ungets(char []);
int gettoken(void);
int nexttoken(void);
int dcl_main(void);
int undcl(void);