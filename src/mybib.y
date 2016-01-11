%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "include/global.h"
    
    void yyerror(const char *s);
    int yylex();
    
%}
%union{
    char* string;
    char carac;
}
%token <string> TYPEREF TYPECHAMP KEY VAL
%left TYPEREF
%left TYPECHAMP
%left KEY
%left VAL
%%

file: bloc file
    |
;

bloc: TYPEREF KEY champs {
    Reference ref = newReference(getType($1), $2);
    initIteratorList(champValList);
    while (hasNextList(champValList)) {
        ChampVal cV = (ChampVal) nextList(champValList);
        setReference(ref, cV->champ, cV->val);
    }
    clearList(champValList);
    setRefManager(refManager, ref);
} '}'
;

champs: TYPECHAMP champs
    |TYPECHAMP VAL {
    ChampVal cV = malloc(sizeof(cV));
    cV->champ = getChamp($1);
    cV->val = $2;
    insertList(champValList, cV);
} champs
    |
;

%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}
