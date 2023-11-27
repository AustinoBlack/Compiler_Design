%{
// C stuff here
#include <stdio.h>
#include "language.tab.h"
#include "symtab.h"
%}

/* regular expressions here */
number_literal   -?[0-9]+
variable_literal [a-z]+
note_literal     &[0-9]|&(1[0-2])

%option NOYYWRAP

%{ 
extern int lines;
extern SymbolTable symboltable;
%}

%%

"Hello"                     {return PRGMBEGIN;}
"Bye"                       {return PRGMEND;}
"as long as:"               {return LOOPHEAD;}
"if:"                       {return IFHEAD;}
"rectangle:"                {return RECTANGLE;}
"pixel:"                    {return PIXEL;}
"music:"                    {return MUSIC;}
"otherwise:"                {return ELSE;}
"is"                        {return ASSIGNMENT;}
"equals"                    {return EQUALS;}
"plus"                      {return PLUS;}
"minus"                     {return MINUS;}
"times"                     {return TIMES;}
"divides"                   {return DIVIDE;}
"&"													{return AND;}
"^"													{return OR;}
"is greater than"           {return GT;}
"is less than"              {return LT;}
"is greater or equal to"    {return GORE;}
"is less or equal to"       {return LORE;}
"Then."                     {return BEGINSTMT;}
"Now."                      {return ENDSTMT;}
"clear"											{return CLEAR;}
"background"								{return BACKGROUND;}
"input"											{return INPUT;}
black												{return BLACK;}
white												{return WHITE;}
red													{return RED;}
cyan												{return CYAN;}
purple											{return PURPLE;}
green												{return GREEN;}
blue												{return BLUE;}
yellow											{return YELLOW;}
orange											{return ORANGE;}
brown												{return BROWN;}
ltred												{return LTRED;}
dkred												{return DKGREY;}
grey												{return GREY;}
ltgreen											{return LTGREEN;}
ltblue											{return LTBLUE;}
ltgrey											{return LTGREY;}
"."                         {return PERIOD;}
","                         {return COMMA;}
[ \t]                       //Whitespace
"\n"                        {lines++;}
{number_literal}            { yylval.intval=atoi(yytext); return NUMBER;}
{variable_literal}		      {	strncpy(yylval.strval, yytext, 256); return VARIABLE;}
{note_literal}              { strncpy(yylval.strval, yytext, 256); return NOTE;}

%%

