/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LANGUAGE_TAB_H_INCLUDED
# define YY_YY_LANGUAGE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VARIABLE = 258,                /* VARIABLE  */
    NUMBER = 259,                  /* NUMBER  */
    NOTE = 260,                    /* NOTE  */
    PRGMBEGIN = 261,               /* PRGMBEGIN  */
    PRGMEND = 262,                 /* PRGMEND  */
    LOOPHEAD = 263,                /* LOOPHEAD  */
    IFHEAD = 264,                  /* IFHEAD  */
    RECTANGLE = 265,               /* RECTANGLE  */
    PIXEL = 266,                   /* PIXEL  */
    MUSIC = 267,                   /* MUSIC  */
    ELSE = 268,                    /* ELSE  */
    ASSIGNMENT = 269,              /* ASSIGNMENT  */
    EQUALS = 270,                  /* EQUALS  */
    PLUS = 271,                    /* PLUS  */
    MINUS = 272,                   /* MINUS  */
    TIMES = 273,                   /* TIMES  */
    DIVIDE = 274,                  /* DIVIDE  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    GT = 277,                      /* GT  */
    LT = 278,                      /* LT  */
    GORE = 279,                    /* GORE  */
    LORE = 280,                    /* LORE  */
    BEGINSTMT = 281,               /* BEGINSTMT  */
    ENDSTMT = 282,                 /* ENDSTMT  */
    BLACK = 283,                   /* BLACK  */
    WHITE = 284,                   /* WHITE  */
    RED = 285,                     /* RED  */
    CYAN = 286,                    /* CYAN  */
    PURPLE = 287,                  /* PURPLE  */
    GREEN = 288,                   /* GREEN  */
    BLUE = 289,                    /* BLUE  */
    YELLOW = 290,                  /* YELLOW  */
    ORANGE = 291,                  /* ORANGE  */
    BROWN = 292,                   /* BROWN  */
    LTRED = 293,                   /* LTRED  */
    DKGREY = 294,                  /* DKGREY  */
    GREY = 295,                    /* GREY  */
    LTGREEN = 296,                 /* LTGREEN  */
    LTBLUE = 297,                  /* LTBLUE  */
    LTGREY = 298,                  /* LTGREY  */
    PERIOD = 299,                  /* PERIOD  */
    COMMA = 300                    /* COMMA  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "language.y"

    int intval;
    char strval[256];
		class Node* node;

#line 115 "language.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LANGUAGE_TAB_H_INCLUDED  */
