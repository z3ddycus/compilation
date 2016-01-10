%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "include/global.h"
    
    void yyerror(const char *s);
    int yylex();
%}
%union{
    char* val;
    char carac;
}
%token <val> CITE NOCITE INCLUDE INPUT BIBNAME
%token <carac> CARAC
%left CARAC
%left CITE
%left NOCITE
%left INCLUDE
%left INPUT
%left BIBNAME
%%

file : latex
;

latex : CITE {printf("Clé : %s\n", $1); insertSortedSet(keys, $1);} latex
    | NOCITE {printf("Clé : %s\n", $1); insertSortedSet(keys, $1);} latex
| INCLUDE {
    printf("Texte trouvé : %s\n", $1);
    insertList(texFiles, $1);
} latex
| INPUT {
    printf("Texte trouvé : %s\n", $1);
    insertList(texFiles, $1);
} latex
    | BIBNAME {printf("Bibname : %s\n", $1); insertList(bibFiles, $1);} latex
    | CARAC latex
    |
;

%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}
