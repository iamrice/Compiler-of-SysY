/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CONST = 258,
    VOID = 259,
    IF = 260,
    WHILE = 261,
    BREAK = 262,
    CONTINUE = 263,
    RETURN = 264,
    ELSE = 265,
    INT = 266,
    IDENT = 267,
    INTCONST = 268,
    GE = 269,
    NE = 270,
    LT = 271,
    GT = 272,
    LE = 273,
    EQ = 274,
    AND = 275,
    OR = 276,
    ASSIGN = 277,
    TIMES = 278,
    MOD = 279,
    OVER = 280,
    PLUS = 281,
    MINUS = 282,
    MARK = 283,
    COMMA = 284,
    SEMICOLON = 285,
    LBRACE = 286,
    RBRACE = 287,
    LPAREN = 288,
    RPAREN = 289,
    LB = 290,
    RB = 291,
    COMA = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "parser.y" /* yacc.c:1921  */

	Program program;
	CompUnit compUnit;
	CompUnits compUnits;
	Decl decl;
	VarDef varDef;
	VarDefs varDefs;
	InitVal initVal;
	InitVals initVals;
	FuncDef funcDef;
	FuncFParam funcFParam;
	FuncFParams funcFParams;
	Block block;
	Blocks blocks;
	Stmt stmt;
	PrimaryExp primaryExp;
	UnaryExp unaryExp;
	UnaryOp unaryOp;
	MulExp mulExp;
	AddExp addExp;
	AddExps addExps;
	FuncRParams funcRParams;
	RelExp relExp;
	EqExp eqExp;
	LAndExp lAndExp;
	LOrExp lOrExp;
	Id id;
	char* symbol;

#line 126 "parser.tab.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
