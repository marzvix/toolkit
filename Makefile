# Makefile for toolkit

CC = gcc
CFLAGS = -g3 -O0 -Wall -Wextra

ARGS =

INSTALDIR = 

all: toolkit.o filetools.o txtools.o

run:
	./toolkit $(ARGS)

install: toolkit
	cp ./toolkit $(INSTALDIR)/

uninstall: $(INSTALDIR)/toolkit
	rm -i $(INSTALDIR)/toolkit

# -----------------------------------------------------------
# cdata.lib
# -----------------------------------------------------------
toolkit.lib: txtools.o filetools.o toolkit.o
	ar rcs $@ $^

txtools.o: txtools.c txtools.h

filetools.o: filetools.c filetools.h

toolkit.o: toolkit.c toolkit.h

tst_txtools: txtools.o

tst_filetools: filetools.o

tst_toolkit: toolkit.o

.PHONY: clean
clean:
	$(RM) *~
	$(RM) #*
	$(RM) .#*
	$(RM) *.o
	$(RM) *.obj
	$(RM) *.map
	$(RM) *.asm
	$(RM) *.exe
	$(RM) *.code
	$(RM) *.core
	$(RM) *.stackdump
