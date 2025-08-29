/*
 * STevie - ST editor for VI enthusiasts.    ...Tim Thompson...twitch!tjt...
 */

/* One (and only 1) of the following 3 defines should be uncommented. */
/* Most of the code is machine-independent.  Most of the machine- */
/* dependent stuff is in window.c */

/*#define ATARI		1	For the Atari 520 ST */
/*#define UNIXPC	1	1 The AT&T UNIX PC (console) */
/*#define TCAP		1	For termcap-based terminals */

#ifdef DOS
#  define FILELENG 32000
#else
#  define FILELENG 64000
#endif
#define NORMAL 0
#define CMDLINE 1
#define INSERT 2
#define APPEND 3
#define FORWARD 4
#define BACKWARD 5
#define WORDSEP " \t\n()[]{},;:'\"-="

#define CHANGED Changed=1
#define UNCHANGED Changed=0

struct charinfo {
	char ch_size;
	char ch_str[6];
};

extern struct charinfo chars[];

extern int State;
extern int Rows;
extern int Columns;
extern char *Realscreen;
extern char *Nextscreen;
extern char *Filename;
extern char *Filemem;
extern char *Filemax;
extern char *Fileend;
extern char *Topchar;
extern char *Botchar;
extern char *Curschar;
extern char *Insstart;
extern int Cursrow, Curscol, Cursvcol;
extern int Prenum;
extern int Debug;
extern int Changed;
extern int Binary;
extern char Redobuff[], Undobuff[], Insbuff[];
extern char *Uncurschar, *Insptr;
extern int Ninsert, Undelchars;


/* main.c */
void filetonext(void);
void nexttoscreen(void);
void updatescreen(void);
void screenclear(void);
void filealloc(void);
void screenalloc(void);
int readfile(char *fname, char *fromp, int nochangename);
void stuffin(char *s);
void addtobuff(char *s, char c1, char c2, char c3, char c4, char c5, char c6);
int vgetc(void);
int vpeekc(void);
int anyinput(void);

/* cmdline.c */
void readcmdline(int firstc);
void badcmd(void);
void gotocmd(int clr, int fresh, int firstc);
void message(char *s);
int writeit(char *fname);
void filemess(char *s);

/* edit.c */
void edit(void);
void insertchar(int c);
int gethexchar(void);
void getout(void);
void cursupdate(void);
void scrolldown(int nlines);
int oneright(void);
int oneleft(void);
void beginline(void);
int oneup(int n);
int onedown(int n);

/* help.c */
void help(void);
void longline(char *p);

/* linefunc.c */
char *nextline(char *curr);
char *prevline(char *curr);
char *coladvance(char *p, int col);
char *alloc(unsigned size);
char *strsave(char *string);
char *ssearch(int dir, char *str);
void dosearch(int dir, char *str);
void repsearch(void);
char *fwdsearch(char *str);
char *bcksearch(char *str);

/* misccmds.c */
void opencmd(void);
int issepchar(char c);
int cntlines(char *pbegin, char *pend);
void fileinfo(void);
void gotoline(int n);
void yankline(int n);
void putline(int k);
void inschar(int c);
void insertstr(char *s);
void appchar(int c);
int canincrease(int n);
void delchar(void);
void delword(int deltrailing);
void delline(int nlines);

/* normal.c */
void normal(int c);
void tabinout(int inout, int num);
void startinsert(char *initstr);
void resetundo(void);

/* window.c */
void windinit(void);
void windgoto(int r, int c);
void windexit(int r);
void windclear(void);
int windgetc(void);
void windstr(char *s);
void windputc(int c);
void windrefresh(void);
void beeep(void);

/* hexchars.c */
void octchars(void);
void hexchars(void);
void decchars(void);
int hextoint(int c);
