# Makefile for toolkit

BENCH = ~/bench

TKDIR = $(BENCH)/toolkit

CC = gcc
CFLAGS = -g3 -O0 -Wall -Wextra -I $(TKDIR) -L $(TKDIR) -ltoolkit

ARGS =

INSTALDIR = 

TSTDIR = $(BENCH)/tests

all: toolkit.o filetools.o txtools.o config.o

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

config.o: config.c config.h

config: config.o toolkit.o filetools.o 

txtools.o: txtools.c txtools.h

filetools.o: filetools.c filetools.h

toolkit.o: toolkit.c toolkit.h

TESTS: $(TSTDIR)/tst_txtools $(TSTDIR)/tst_filetools $(TSTDIR)/tst_toolkit

$(TSTDIR)/tst_txtools: $(TSTDIR)/tst_txtools.c $(TKDIR)/toolkit.lib


$(TSTDIR)/tst_filetools: $(TSTDIR)/tst_filetools.c $(TKDIR)/toolkit.lib

$(TSTDIR)/tst_toolkit: $(TSTDIR)/tst_toolkit.c $(TKDIR)/toolkit.lib

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
