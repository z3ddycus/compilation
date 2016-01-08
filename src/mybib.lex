%{
#include <stdio.h>
#include <stdlib.h>
#include "include/mybib.tab.h"

%}

%%

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
    yyparse();
}
