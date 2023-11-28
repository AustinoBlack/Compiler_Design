%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "opcodes.h"
#include "helper.h"
#include "symtab.h"

int lines = 1;

extern int yylex();
extern int yyparse();
void yyerror(const char* msg);
extern SymbolTable symboltable;
%}

%union {
    int intval;
    char strval[256];
    class Node* node;
}

%token<strval> VARIABLE
%token<intval> NUMBER
%token<intval> NOTE
%token PRGMBEGIN
%token PRGMEND
%token LOOPHEAD
%token IFHEAD
%token RECTANGLE
%token PIXEL
%token MUSIC
%token ELSE
%token ASSIGNMENT
%token EQUALS
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token AND
%token OR
%token GT
%token LT
%token GORE
%token LORE
%token BEGINSTMT
%token ENDSTMT
%token CLEAR
%token BACKGROUND
%token INPUT
%token BLACK
%token WHITE
%token RED
%token CYAN
%token PURPLE
%token GREEN
%token BLUE
%token YELLOW
%token ORANGE
%token BROWN
%token LTRED
%token DKGREY
%token GREY
%token LTGREEN
%token LTBLUE
%token LTGREY
%token PERIOD
%token COMMA

%define parse.error verbose

%type<node> program code statement clear_statement background_statement /*input_statement*/ loop_statement if_statement assignment_statement rectangle_statement pixel_statement music_statement expression factor term compound_condition condition comparison /*number_literal*/ note_literal; 
%type<intval> color_literal

%%
program: PRGMBEGIN code PRGMEND { 
	$$ = new Node("program"); 
	$$->add_child($2); 
	//$$->visit(0); 
	$$->generate_code();
}; 

code: statement code { Node* n = new Node("code"); n->add_child($1); n->add_child($2); $$ = n; }
    | statement { $$ = $1; }
    ;

statement: clear_statement { $$ = $1; }
	   | background_statement { $$ = $1; }
	   | loop_statement { $$ = $1; }
           | if_statement{ $$ = $1; }
           | assignment_statement { $$ = $1; }
           | rectangle_statement { $$ = $1; }
           | pixel_statement { $$ = $1; }
           | music_statement { $$ = $1; }
           ;

clear_statement: CLEAR PERIOD {
	$$ = new Node("clear");
};

background_statement: BACKGROUND color_literal PERIOD{
	Constant* c = new Constant("background");
	c->set_value($2);
	$$ = c;
};
/*
input_statement: INPUT PERIOD {

};
*/
loop_statement: LOOPHEAD compound_condition BEGINSTMT code ENDSTMT { 
	$$ = new Node("loop"); 
	$$->add_child($2); 
	$$->add_child($4); 
};

if_statement: IFHEAD compound_condition BEGINSTMT code ENDSTMT { 
	$$ = new Node("if"); 
	$$->add_child($2); 
	$$->add_child($4); 
};

assignment_statement: VARIABLE ASSIGNMENT expression PERIOD {
	Node* n = new Node("assignment");
	Identifier* id = new Identifier("variable");
	id->set_value(string($1));
	n->add_child(id);
	n->add_child($3);
	$$ = n;
};

rectangle_statement: RECTANGLE color_literal COMMA expression COMMA expression COMMA expression COMMA expression PERIOD { 
	$$ = new Node("rectangle");
	Constant* c = new Constant("color"); 
	c->set_value($2); 
	$$->add_child(c); 
	$$->add_child($4); 
	$$->add_child($6); 
	$$->add_child($8); 
	$$->add_child($10); 
};

pixel_statement: PIXEL color_literal COMMA expression COMMA expression PERIOD { 
	$$ = new Node("pixel");
	Constant* c = new Constant("color");
	c->set_value($2); 
	$$->add_child(c); 
	$$->add_child($4); 
	$$->add_child($6); 
};

music_statement: MUSIC note_literal PERIOD {
//	$$ = new Node("music"); 
//	$$->add_child($2); 
	$$ = $2;
};

expression: factor { $$ = $1; } 
	   | expression PLUS factor { Node* n = new Node("plus"); n->add_child($1); n->add_child($3); $$=n; } 
	   | expression MINUS factor { Node* n = new Node("minus"); n->add_child($1); n->add_child($3); $$=n; }
           ;

factor: term { $$ = $1; } 
 	     | factor TIMES term { Node* n = new Node("times"); n->add_child($1); n->add_child($3); $$=n; } 
	     | factor DIVIDE term { Node* n = new Node("divide"); n->add_child($1); n->add_child($3); $$=n; }
      	     ; 

term: VARIABLE { Identifier* id = new Identifier("variable"); id->set_value($1); $$ = id;  } 
		| NUMBER { Constant* n = new Constant( "number" ); n->set_value($1); $$ = n; }
    		;

compound_condition: condition {$$ = $1; } 
		  | condition AND condition {Node* n = new Node("and"); n->add_child($1), n->add_child($3); $$=n;} 
	          | condition OR condition {Node* n = new Node("or"); n->add_child($1), n->add_child($3); $$=n;}
                  ; 

condition: expression comparison expression { Node* n = new Node("condition"); n->add_child($1); n->add_child($2); n->add_child($3); $$=n; };

comparison : EQUALS { $$ = new Node("equals"); }
		    | GT { $$ = new Node("gt"); }
		    | LT { $$ = new Node("lt"); }
		    | GORE { $$ = new Node("gore"); }
		    | LORE { $$ = new Node("lore"); }
	            ;

//number_literal: NUMBER { Constant* n = new Constant("number_literal"); n->set_value($1); $$ = n; };

color_literal: BLACK { $$ = 0; }
	     | WHITE { $$ = 1; } 
	     | RED { $$ = 2; } 
             | CYAN { $$ = 3; } 
 	     | PURPLE { $$ = 4; } 
             | GREEN { $$ = 5; } 
             | BLUE { $$ = 6; } 
             | YELLOW { $$ = 7; } 
             | ORANGE { $$ = 8; } 
             | BROWN { $$ = 9; } 
             | LTRED { $$ = 10; } 
             | DKGREY { $$ = 11; } 
             | GREY { $$ = 12; } 
             | LTGREEN { $$ = 13; } 
             | LTBLUE { $$ = 14; } 
             | LTGREY { $$ = 15; }
             ;              

note_literal: NOTE { Constant* n = new Constant("note_literal"); n->set_value($1); $$ = n; };


%%

struct Node* cur_node = NULL;
int main( int argc, char* argv[])
{		
  setup_sound();
  play_sound(2145,60);
  play_sound(3215,60);
  play_sound(2145,60);
  rts();
  yyparse();
  print_program();
}

void yyerror(const char* msg)
{
	printf( "Parse error in line %d: %s\n", lines, msg );
	exit(-1);	
}
