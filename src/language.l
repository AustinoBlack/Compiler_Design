%{
// C stuff here
#include <stdio.h>
#include "language.tab.h"
#include "symtab.h"
%}

/* regular expressions here */
number_literal   -?[0-9]+
variable_literal [a-z]+

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
"&"			    {return AND;}
"^"			    {return OR;}
"is greater than"           {return GT;}
"is less than"              {return LT;}
"is greater or equal to"    {return GORE;}
"is less or equal to"       {return LORE;}
"Then."                     {return BEGINSTMT;}
"Now."                      {return ENDSTMT;}
"clear"			    {return CLEAR;}
"background"		    {return BACKGROUND;}
"input"			    {return INPUT;}
black			    {return BLACK;}
white			    {return WHITE;}
red			    {return RED;}
cyan			    {return CYAN;}
purple			    {return PURPLE;}
green                       {return GREEN;}
blue			    {return BLUE;}
yellow			    {return YELLOW;}
orange			    {return ORANGE;}
brown			    {return BROWN;}
ltred			    {return LTRED;}
dkred			    {return DKGREY;}
grey			    {return GREY;}
ltgreen			    {return LTGREEN;}
ltblue			    {return LTBLUE;}
ltgrey			    {return LTGREY;}
😺0						{return A;}
😺1           {return ASHARP;}
😺2           {return B;}
😺3           {return C;}
😺4           {return CSHARP;}
😺5           {return D;}
😺6           {return DSHARP;}
😺7           {return E;}
😺8           {return F;}
😺9           {return FSHARP;}
😺10          {return G;}
😺11          {return GSHARP;}
😺12          {return HIGHA;}
"."                         {return PERIOD;}
","                         {return COMMA;}
[ \t]                       //Whitespace
"\n"                        {lines++;}
{number_literal}            { yylval.intval=atoi(yytext); return NUMBER;}
{variable_literal}	    { strncpy(yylval.strval, yytext, 256); return VARIABLE;}

%%

