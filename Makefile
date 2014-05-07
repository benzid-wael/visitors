# Makefile for xvisitors
# Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
# All Rights Reserved
# Under the GPL license version 2

.PHONY: all clean

DEBUG?= -g
CFLAGS?= -O2 -Wall -W $(shell pkg-config --cflags glib-2.0)
LFLAGS ?= $(shell pkg-config --libs glib-2.0)

OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
PRGNAME = xvisitors

all: $(PRGNAME)

$(PRGNAME): $(OBJ)
	$(CC) -o $(PRGNAME) $(CFLAGS) $(LFLAGS) $(DEBUG) $(OBJ)

.c.o:
	$(CC) -c $(CFLAGS) $(DEBUG) $(COMPILE_TIME) $<

clean:
	rm -rf $(PRGNAME) *.o
	find -name '*~' -delete
	find -name '*.sw[po]' -delete
