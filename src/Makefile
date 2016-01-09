LEX=flex
YACC=bison
CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
LDFLAGS=-ll
LFLAGS=-D_POSIX_SOURCE -DYY_NO_INPUT --nounput

SRC=src
HEADER=$(SRC)/include
BIN=bin
OBJ=obj

EXEC=mybib

all: $(EXEC)

$(EXEC): lex.yy.o mybib.tab.o
	$(CC) $+ -o $@ $(LDFLAGS)

lex.yy.c: mybib.lex mybib.tab.h
	$(LEX) -o $@ $(LFLAGS) $<

lex.yy.h: mybib.lex
	$(LEX) --header-file=$@ $(LFLAGS) $<

mybib.tab.c: mybib.y lex.yy.h
	$(YACC) -o $@ $< -d -v

mybib.tab.h: mybib.y lex.yy.h
	$(YACC) -o $@ $< -d -v

%.o: %.c
	$(CC) $(CFLAGS) $< -c

clean:
	-rm $(EXEC) lex.yy.* mybib.tab.* *.output
