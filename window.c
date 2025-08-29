/*
 * STevie - ST editor for VI enthusiasts.    ...Tim Thompson...twitch!tjt...
 */

#include "stevie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ATARI
#include <osbind.h>
#define EscSeq(x) Cconout('\033');Cconout(x);
#endif
#ifdef UNIXPC
#include <sys/window.h>
#endif
#ifdef TCAP
#include <curses.h>
#endif
#ifdef DOS
#include <i86.h>
static void __far *Screen;

#endif

void windinit(void)
{
#ifdef ATARI
	Columns=80;
	Rows=25;
	Cursconf(1,NULL);
#endif
#ifdef UNIXPC
        struct uwdata uw;
        
	winit();
	if ( ioctl(0,WIOCGETD,&uw) == -1
	  && ioctl(1,WIOCGETD,&uw) == -1
	  && ioctl(2,WIOCGETD,&uw) == -1 ) {
		fprintf(stderr,"*** ERROR *** Not a window!\n");
		windexit(1);
	}
	Columns = uw.uw_width / uw.uw_hs;
	Rows = uw.uw_height / uw.uw_vs;
	cbreak();
	nonl();
	noecho();
#endif
#ifdef TCAP
	char *p = getenv("TERM");

	initscr();
	Columns = getmaxx(stdscr);
	Rows = getmaxy(stdscr);
	cbreak();
	nonl();
	noecho();
#endif
#ifdef DOS
	int mode;
	Columns=80;
	Rows=25;
	__asm {
		mov ah,0fh
		int 10h
		mov [mode],ax
	}
	if ((mode & 0xff) == 7) Screen = MK_FP(0xb000, 0);
	else Screen = MK_FP(0xb800, 0);
#endif
}

void windgoto(int r, int c)
{
#ifdef UNIXPC
	printf("\033[%d;%dH",r+1,c+1);
#endif
#ifdef ATARI
	EscSeq('Y');
	Cconout(r+040);
	Cconout(c+040);
#endif
#ifdef TCAP
	move(r,c);
#endif
#ifdef DOS
	__asm {
		mov ah,2
		mov dh,byte ptr [r]
		mov dl,byte ptr [c]
		xor bh,bh
		int 10h
	}
#endif
}

void windexit(int r)
{
#ifdef UNIXPC
	nocbreak();
	nl();
	echo();
	wexit();
#endif
#ifdef TCAP
	nocbreak();
	nl();
	echo();
	endwin();
#endif
	exit(r);
}

void windclear(void)
{
#ifdef UNIXPC
	printf("\033[H\033[J");
#endif
#ifdef ATARI
	Cconws("\033H\033J");
#endif
#ifdef TCAP
	clear();
	refresh();
#endif
#ifdef DOS
	unsigned __far *scr = Screen;
	while (FP_OFF(scr) < Rows * Columns * 2) {
		*scr++ = 0x0700;
	}
#endif
}

int windgetc(void)
{
#ifdef ATARI
	return(Cnecin());
#elif DOS
	int r = 0;
	__asm {
	l:
		mov ah,10h
		int 16h
		mov byte ptr [r],al
	}
	return r;
#else
	return(getchar());
#endif
}
void windstr(char *s)
{
#ifdef ATARI
	Cconws(s);
#endif
#ifdef UNIXPC
	printf("%s",s);
#endif
#ifdef TCAP
	addstr(s);
	refresh();
#endif
#ifdef DOS
	while (*s) windputc(*s++);
#endif
}

void windputc(int c)
{
#ifdef ATARI
	Cconout(c);
#endif
#ifdef UNIXPC
	putchar(c);
#endif
#ifdef TCAP
	addch(c);
#endif
#ifdef DOS
	__asm {
		mov ah,0eh
		mov al,byte ptr [c]
		mov bx,7
		int 10h
	}
#endif
}

void windrefresh(void)
{
#ifdef TCAP
	refresh();
#endif
}

void beeep(void)
{
#ifdef ATARI
	Cconout('\007');
#else
	putchar('\007');
#endif
}
