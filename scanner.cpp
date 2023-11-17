#include "scanner.h"
#include <iostream>

char* in_string;
char* current_position;
int i = 0;

void initialize_state(char* input)
{
   in_string = current_position = input;
}

Token next_token()
{
   Token tok;
   tok.value = 0;
 
   int tracker = 0;
   if (!current_position || *current_position == '\0') {
      tok.tok_id = END_OF_STRING;
      return tok;
   }  
        //printf( "looking at: %c\n", *current_position ); //DEBUG
   switch ( *current_position )
   {
        case '+':
            tok.tok_id = TOK_PLUS; 
            current_position++;
            break;

        case '-':
            tok.tok_id = TOK_MINUS; 
            current_position++;
            break;

        case '*':
            tok.tok_id = TOK_TIMES; 
            current_position++;
            break;

        case '/':
            tok.tok_id = TOK_DIV; 
            current_position++;
            break;

        case '%':
            tok.tok_id = TOK_MOD; 
            current_position++;
            break;

        case '(':
            tok.tok_id = TOK_LPAREN; 
            current_position++;
            break;

        case ')':
            tok.tok_id = TOK_RPAREN; 
            current_position++;
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            do {
                tok.value *= 10;
                tracker = *current_position - '0';
                tok.value += tracker;
                tok.tok_id = TOK_INT;

                current_position++;               
                tracker = *current_position - '0';

            }while( tracker >= 0 && tracker <= 9 );
            break;
   } 
   
   return tok;
}
