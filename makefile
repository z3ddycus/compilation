LEX=flex
YACC=bison
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall
LDFLAGS=-ll -lm
LFLAGS=-D_POSIX_SOURCE -DYY_NO_INPUT --nounput

SRC=src
HEADER=$(SRC)/include
BIN=bin
OBJ=obj

EXEC=$(BIN)/mybib

$(EXEC): $(OBJ)/lex.yy.o $(OBJ)/mybib.tab.o
	@mkdir -p BIN
	@mkdir -p OBJ
	$(CC) $+ -o $@ $(LDFLAGS)

$(SRC)/lex.yy.c: $(SRC)/mybib.lex $(HEADER)/mybib.tab.h
	$(LEX) -o $@ $(LFLAGS) $<
	@echo "src ok"

$(HEADER)/lex.yy.h: $(SRC)/mybib.lex
	$(LEX) —header-file=$@ $(LFLAGS) $<
	@echo "lex yy h ok"

$(SRC)/mybib.tab.c: $(SRC)/mybib.y $(HEADER)/lex.yy.h
	$(YACC) -o $@ $< -d -v
	@echo "yacc C ok"

$(HEADER)/mybib.tab.h: $(SRC)/mybib.y $(HEADER)/lex.yy.h
	$(YACC) -o $@ $< -d -v
	@echo "yacc H ok"

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $< -c

clean:
	-rm $(EXEC) $(OBJ) $(SRC)/lex.yy.* $(HEADER)/lex.yy.* $(SRC)/mybib.tab.* $(HEADER)/mybib.tab.*
