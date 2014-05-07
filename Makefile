# Makefile for xvisitors
# Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
# All Rights Reserved
# Under the GPL license version 2

DEBUG?= -g
CFLAGS?= -O2 -Wall -W $(shell pkg-config --cflags glib-2.0)
LFLAGS ?= $(shell pkg-config --libs glib-2.0)
CCOPT= $(CFLAGS)


OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
PRGNAME = xvisitors

all: $(PRGNAME)

$(PRGNAME): $(OBJ)
	$(CC) -o $(PRGNAME) $(CCOPT) $(LFLAGS) $(DEBUG) $(OBJ)

.c.o:
	$(CC) -c $(CCOPT) $(DEBUG) $(COMPILE_TIME) $<

clean:
	rm -rf $(PRGNAME) *.o
	find -name '*~' -delete
	find -name '*.sw[po]' -delete
