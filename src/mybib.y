%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.h"
    void yyerror(const char *s);
%}

%token NUMBER TOKHEAT STATE TOKTARGET TOKTEMPERATURE

%%

commands: /* empty */
| commands command
;

command:
heat_switch
|
target_set
;

heat_switch:
TOKHEAT STATE
{
    printf("\tHeat turned on or off\n");
}
;

target_set:
TOKTARGET TOKTEMPERATURE NUMBER
{
    printf("\tTemperature set\n");
}
;
%%
void yyerror(const char *s) {
    fprintf(stderr,"%s\n", s);
}
