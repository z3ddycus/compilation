TARGET = mybib

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(filter-out $(OBJDIR)/lex.yy.o $(OBJDIR)/$(TARGET).tab.o, $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o))

LEX = flex
YACC = bison
CC = gcc
CFLAGS = -std=c99 -pedantic -g -Wall
LDFLAGS = -lfl -lm
LFLAGS = -D_POSIX_SOURCE -o $@ -DYY_NO_INPUT --nounput

all: pre $(OBJECTS) $(BINDIR)/$(TARGET)

pre:
	mkdir -p $(OBJDIR) $(BINDIR)

$(BINDIR)/$(TARGET): $(OBJECTS) $(OBJDIR)/lex.yy.o $(OBJDIR)/$(TARGET).tab.o
	$(CC) $+ -o $@ $(LDFLAGS)

$(SRCDIR)/lex.yy.c: $(SRCDIR)/$(TARGET).lex $(SRCDIR)/$(TARGET).tab.h
	$(LEX) -o $(SRCDIR)/lex.yy.c -D_POSIX_SOURCE $<

$(SRCDIR)/lex.yy.h: $(SRCDIR)/$(TARGET).lex
	$(LEX) --header-file=$@ $(LFLAGS) $<

$(SRCDIR)/$(TARGET).tab.c $(SRCDIR)/$(TARGET).tab.h: $(SRCDIR)/$(TARGET).y $(SRCDIR)/lex.yy.h
	$(YACC) -o $(SRCDIR)/$(TARGET).tab.c $< -d

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) $< -c

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) $< -c
	@echo "Terminée."

clean:
	-rm -rf $(OBJDIR) $(SRCDIR)/lex.yy.* $(SRCDIR)/$(TARGET).tab.*

cleaner:
	-rm -rf $(BINDIR) $(OBJDIR) $(SRCDIR)/lex.yy.* $(SRCDIR)/$(TARGET).tab.*
