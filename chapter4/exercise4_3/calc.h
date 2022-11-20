#define NUMBER '0'
#define FUNCTION 'f'
void push(double);
double pop(void);
double top(void);
void clear(void);
int getop(char []);
int getch(void);
void ungetch(int);
void ungets(char []);
int getch_s(void);
void ungetch_s(int);
int getword(char []);
int is_func(char []);
int is_num(char []);
int getop_line(char []);
int getop_static(char []);