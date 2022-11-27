enum { NAME, PARENS, BRACKETS };
int getch(void);
void ungetch(int);
void ungets(char []);
int gettoken(void);
int dcl_main(void);