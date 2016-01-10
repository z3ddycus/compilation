%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "include/global.h"
    
    void yyerror(const char *s);
    int yylex();
%}
%union{
    char* string;
    char carac;
}
%token <string> TYPEREF TYPECHAMP KEY
%token <carac> CARAC
%left CARAC
%left TYPEREF
%left TYPECHAMP
%left KEY
%%

file : TYPEREF '{' KEY ',' '\n' ' '' 'cleValeur
    |

cleValeur : TYPECHAMP '=' '{' CARAC '}' '\n' '}' file
    | TYPECHAMP '=' '{' CARAC '}' ',' ' ' \n' ' '' 'cleValeur

%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}
