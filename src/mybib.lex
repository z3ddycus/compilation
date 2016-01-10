%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/global.h"
#include "include/sorted_set.h"
#include "include/list.h"
#include "mybib.tab.h"

SortedSet keys;
List files;
char* bibName;
%}
CITE \\cite\{[^\}]+\}
NOCITE \\nocite\{[^\}]+\}
BIBNAME \\bibliography\{[^\}]+\}
INCLUDE \\include\{[^\}]+\}
CARAC .|\n
%%
{CITE} {
    const size_t size = yyleng - 7;
    char* key = malloc(size + 1);
    memcpy(key, &yytext[6], size);
    key[size] = '\0';
    insertSortedSet(keys, key);
    yylval.val = key;
    return CITE;
}

{NOCITE} {
    const size_t size = yyleng - 9;
    char* key = malloc(size + 1);
    memcpy(key, &yytext[8], size);
    key[size] = '\0';
    insertSortedSet(keys, key);
    yylval.val = key;
    return NOCITE;
}

{BIBNAME} {
    const size_t size = yyleng - 15;
    bibName = malloc(size + 1);
    memcpy(bibName, &yytext[14], size);
    bibName[size] = '\0';
    printf("%s\n", bibName);
}

{INCLUDE} {
    const size_t size = yyleng - 10;
    char* file = malloc(size + 1);
    memcpy(file, &yytext[9], size);
    file[size] = '\0';
    insertList(files, file);
}

{CARAC} {
    yylval.carac = yytext[0];
    return CARAC;
}
%%
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

    refManager = newRefManager();

    keys = newSortedSet((int (*) (void*, void*)) strcmp);
    files = newList((int (*) (void*, void*)) strcmp);

    yyparse();

    // Parcours des include.
    initIteratorList(files);
    while (hasNextList(files)) {
        yyin = fopen(nextList(files), "r");
        yyparse();
    }

    // Passage sur le .bib.

}
