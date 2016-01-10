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

file : randomThing file
    | TYPEREF {printf("Type : %s\n", $1);} bloc file
    | {printf("r3\n");}
;

bloc : {printf("r4\n");} '{' KEY '\n' enumChamps '}'
;

enumChamps: {printf("r5\n");} champ ',' '\n' enumChamps
    | {printf("r6\n");} champ '\n'
;

champ: {printf("r7\n");} TYPECHAMP {printf("Champ : %s\n", $2);} '=' '{' phrase '}'
;

phrase: {printf("r8\n");} CARAC phrase
    |
;

randomThing: CARAC {printf("Carac : %c\n", $1);} | ',' | '=' | '\n';

%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}
