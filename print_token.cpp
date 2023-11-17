#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

void print_token(Token tok)
{
   switch(tok.tok_id) {
      case ERROR:
	      printf("Syntax Error!");
	      exit(-1);
      break;
      case TOK_INT:
	      printf("<INT, %d>", tok.value);
	      break;
      case TOK_PLUS:
	      printf("<+>");
	      break;
      case TOK_MINUS:
	      printf("<->");
	      break;
      case TOK_TIMES:
	      printf("<*>");
	      break;
      case TOK_DIV:
	      printf("</>");
	      break;
      case TOK_MOD:
	      printf("<%%>");
	      break;
      case TOK_LPAREN:
	      printf("<(>");
	      break;
      case TOK_RPAREN:
	      printf("<)>");
	      break;
   }
}
