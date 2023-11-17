%{
#include "numeral.tab.h"
%}
LOW [0-3]
FOUR 4
HIGH [5-8]
NINE 9
%option NOYYWRAP

%%

{LOW} { yylval.value = atoi(yytext); return LOW;}
{FOUR} { yylval.value = 4; return FOUR;}
{HIGH} { yylval.value = atoi(yytext) - 5; return HIGH;}
{NINE} { yylval.value = 9; return NINE;}
[ \t\n]+ {return WS;}

%%

