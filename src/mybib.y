%{
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(const char *s);
    int yylex();
%}
%union{
    char* val;
    char carac;
}
%token <val> CITE NOCITE INCLUDE
%token <carac> CARAC
%left CARAC
%left CITE
%left NOCITE
%%

file : text
;

text : text CITE text {printf("%s\n", $2);}
    | text NOCITE text {printf("%s\n", $2);}
    | text CARAC text
    | CARAC
    |
;

%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}
