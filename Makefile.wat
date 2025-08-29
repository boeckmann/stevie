# quick&dirty Makefile for Watcom C

OBJ  = main.obj edit.obj linefunc.obj normal.obj cmdline.obj hexchars.obj
OBJ += misccmds.obj window.obj help.obj

CFLAGS = -q -os -DDOS

default : stevie.exe

.c.obj:
	wcc $(CFLAGS) $<

stevie.exe : $(OBJ)
	wcl -q -Fe=stevie.exe $(OBJ) 

clean: .symbolic
	rm -f *.obj *.err stevie.exe
