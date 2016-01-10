%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/global.h"
#include "mybib.tab.h"

char* filePrefix;
%}
CITE \\cite\{[^\}]+\}
NOCITE \\nocite\{[^\}]+\}
BIBNAME \\bibliography\{[^\}]+\}
INCLUDE \\include\{[^\}]+\}
INPUT \\input\{[^\}]+\}

TYPEREF @Article|@Book|@Booklet|@Conference|@Inbook|@Incollection|@Inproceedings|@Manual|@Mastersthesis|@Misc|@Phdthesis|@Proceedings|@Techreport|@Unpublished
TYPECHAMP address|abstract|annote|author|booktitle|chapter|crossref|edition|editor|eprint|howpublished|institution|isbn|journal|key|month|note|number|organization|pages|publisher|school|series|title|type|url|volume|year
KEY [^,|\n|@|{|}|\ ]+:[^,|\n|@|{|}|\ ]+,

CARAC [^\ ]

%s latex
%s bibtex
%%
<latex>{CITE} {
    const size_t size = yyleng - 7;
    char* key = malloc(size + 1);
    memcpy(key, &yytext[6], size);
    key[size] = '\0';
    insertSortedSet(keys, key);
}

<latex>{NOCITE} {
    const size_t size = yyleng - 9;
    char* key = malloc(size + 1);
    memcpy(key, &yytext[8], size);
    key[size] = '\0';
    insertSortedSet(keys, key);
}

<latex>{BIBNAME} {
    const size_t size = yyleng - 11;
    char* file = malloc(size + 1);
    file = malloc(size + 1);
    memcpy(file, &yytext[14], size - 4);
    file[size - 4] = '.';
    file[size - 3] = 'b';
    file[size - 2] = 'i';
    file[size - 1] = 'b';
    file[size] = '\0';
    insertList(bibFiles, file);
}

<latex>{INCLUDE} {
    const size_t size = yyleng - 6;
    char* file = malloc(size + 1);
    memcpy(file, &yytext[9], size - 4);
    file[size - 4] = '.';
    file[size - 3] = 't';
    file[size - 2] = 'e';
    file[size - 1] = 'x';
    file[size] = '\0';
    insertList(texFiles, file);
}

<latex>{INPUT} {
    const size_t size = yyleng - 4;
    char* file = malloc(size + 1);
    memcpy(file, &yytext[9], size - 4);
    file[size - 4] = '.';
    file[size - 3] = 't';
    file[size - 2] = 'e';
    file[size - 1] = 'x';
    file[size] = '\0';
    insertList(texFiles, file);
}

<bibtex>{TYPEREF} {
    size_t size = strlen(yytext);
    yylval.string = malloc(size);
    memcpy(yylval.string, &yytext[1], size - 1);
    yylval.string[size] = '\0';
    printf("Ref : %s\n", yylval.string);
    return TYPEREF;
}

<bibtex>{TYPECHAMP} {
    printf("Champ : %s\n", yytext);
    size_t size = strlen(yytext);
    yylval.string = malloc(size + 1);
    memcpy(yylval.string, &yytext[0], size);
    yylval.string[size] = '\0';
    return TYPECHAMP;
}

<bibtex>{KEY} {
    size_t size = strlen(yytext) - 1;
    yylval.string = malloc(size + 1);
    memcpy(yylval.string, &yytext[0], size);
    yylval.string[size] = '\0';
    printf("Key : %s\n", yylval.string);
    return KEY;
}

<bibtex>\{ return '{';
<bibtex>\} return '}';
<bibtex>\n return '\n';
<bibtex>, return ',';
<bibtex>= return '=';

<bibtex>{CARAC} {
    yylval.carac = yytext[0];
    return CARAC;
}

.|\n {}
%%
int yywrap(void) {
    if (lengthList(texFiles) > 0) {
        char* file = popList(texFiles);
        char* s = malloc(strlen(filePrefix) + strlen(file) + 1);
        sprintf(s, "%s%s", filePrefix, file);
        fclose(yyin);
        yyin = fopen(s, "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier de nom %s.\n", file);
            exit(0);
        }

        BEGIN(latex);
        return 0;
    }

    if (lengthList(bibFiles) > 0) {
        char* file = popList(bibFiles);
        char* s = malloc(strlen(filePrefix) + strlen(file) + 1);
        sprintf(s, "%s%s", filePrefix, file);
        fclose(yyin);
        yyin = fopen(s, "r");
        if (yyin == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier de nom %s.\n", file);
            exit(0);
        }

        BEGIN(bibtex);
        return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    /**
    -b 1 arg  : genere un bibtex a partir d'un .tex
    -c 1 arg  : verifie que chaque toutes les entrées ont une entrée propre
    -e 3 args : extraction d'un bibtex par filtre regexp
    -k 1 arg  : normalise les clés d'un .bib
    -s 1 arg  : extraction des champs pour tri
    -t 2 args : ne garde que les entrées de type t
    -u 1 arg  : supprime les doublons
    -o 1 arg  : redirection de la sortie standard dans un fichier
    */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    // Calcul du prefixe
    char* p = strchr(argv[1], '/');
    if (p != NULL) {
        size_t size = p - argv[1] + 1;
        filePrefix = malloc(size + 1);
        memcpy(filePrefix, argv[1], size);
        filePrefix[size] = '\0';
        printf("Pref : %s\n", filePrefix);
    } else {
        filePrefix = malloc(1);
        filePrefix[0] = '\0';
    }

    refManager = newRefManager();

    keys = newSortedSet((int (*) (void*, void*)) strcmp);
    texFiles = newList((int (*) (void*, void*)) strcmp);
    bibFiles = newList((int (*) (void*, void*)) strcmp);


    BEGIN(latex);
    yyparse();
}
