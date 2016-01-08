%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "include/lex.yy.h"
    void yyerror(const char *s);
    %}
%token NOMBRE
%%
ligne   : ligne expr '\n' {printf("resultat : %f \n",$2);}
| ligne '\n'
|
;
expr    : expr '+' terme {$$=$1+$3;}
| expr '-' terme {}
| terme
;
terme   : terme '*' facteur {}
| terme '/' facteur {}
| facteur
;
facteur : '-' facteur {}
| '(' expr ')' {}
| NOMBRE {$$ = $1;}
;
%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}

