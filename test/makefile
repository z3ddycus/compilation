TARGET = test

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

$(BINDIR)/$(TARGET): $(OBJDIR)/*.o
	$(CC) $+ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) $< -c
	@echo "Terminée."

clean:
	-rm -rf $(OBJDIR)

cleaner:
	-rm -rf $(BINDIR) $(OBJDIR)
