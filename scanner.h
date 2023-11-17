#ifndef SCANNER_H
#define SCANNER_H

enum token_type {
	ERROR, 
	TOK_INT,
	TOK_PLUS,
	TOK_MINUS,
	TOK_TIMES,
	TOK_DIV,
	TOK_MOD,
	TOK_LPAREN,
	TOK_RPAREN,
	END_OF_STRING
};

typedef struct Token {
   token_type tok_id=ERROR; //required
   int value=0; //optional
} Token; 

void initialize_state(char* input);
Token next_token();
void print_token(Token t);
#endif
