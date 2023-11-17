%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
void yyerror(const char* msg);

void repeat(char symbol, int num)
{
    for (int i=0; i < num; ++i){
        printf("%c", symbol);
    }
}
%}

%union {
    int value;
}

%token <value> LOW
%token <value> HIGH
%token <value> FOUR
%token <value> NINE
%token WS

%define parse.error verbose

%%

numbers: number | number WS numbers;

number: thousands hundreds tens ones { printf("\n");};

thousands: LOW { repeat('M', $1); };

hundreds: LOW { repeat('C', $1); } |
          FOUR {printf("CD");} |
          HIGH { printf("D"); repeat('C', $1);} |
          NINE {printf("CM");};

tens: LOW { repeat('X', $1); } |
      FOUR {printf("XL");} |
      HIGH { printf("L"); repeat('X', $1);} |
      NINE {printf("XL");};

ones: LOW { repeat('I', $1); } |
      FOUR {printf("IV");} |
      HIGH { printf("V"); repeat('I', $1);} |
      NINE {printf("IX");};
%%

int main(int argc, char* argv[]) {
    yyparse();
}

void yyerror(const char* msg) {
    printf("Parse Error: %s\n", msg);
    exit(-1);
}
