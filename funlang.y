%{
 #include "Lexer.h"
 #include "Parser.h"
%}

%token FUNCTION_KEYWORD IF ELSE INT_KEYWORD STR_KEYWORD BOOL_KEYWORD
%token BOOL_LITERAL INT_LITERAL STR_LITERAL GIVES_TYPE IDENTIFIER OTHER

%output  "Parser.c"
%defines "Parser.h"

%union{
 char name[16];
 intmax_t val;
}
%lex-param {yyscan_t scanner}

%%

function: FUNCTION_KEYWORD IDENTIFIER '(' parameters ')' GIVES_TYPE INT_KEYWORD '{' statement '}'
|         FUNCTION_KEYWORD IDENTIFIER '(' parameters ')' GIVES_TYPE STR_KEYWORD '{' statement '}'
|         FUNCTION_KEYWORD IDENTIFIER '(' parameters ')' GIVES_TYPE BOOL_KEYWORD '{' statement '}';

parameters: parameter
|           %empty;

parameter: INT_KEYWORD                IDENTIFIER
|          parameter ',' INT_KEYWORD  IDENTIFIER
|          STR_KEYWORD                IDENTIFIER
|          parameter ',' STR_KEYWORD  IDENTIFIER
|          BOOL_KEYWORD               IDENTIFIER
|          parameter ',' BOOL_KEYWORD IDENTIFIER;

call_parameters: parameter
|                %empty;


call_parameter: IDENTIFIER
|               parameter ',' IDENTIFIER;


var_definition: INT_KEYWORD IDENTIFIER '=' INT_LITERAL ';'
|               INT_KEYWORD IDENTIFIER ';'
|               STR_KEYWORD IDENTIFIER '=' STR_LITERAL ';'
|               STR_KEYWORD IDENTIFIER ';'
|               BOOL_KEYWORD IDENTIFIER '=' BOOL_LITERAL ';'
|               BOOL_KEYWORD IDENTIFIER ';' ;

function_call: IDENTIFIER '(' call_parameters ')';

boolean_statement: '(' IDENTIFIER "==" IDENTIFIER ')' /* TODO: Make sure this only works for ints */
|                  '(' IDENTIFIER ')'                 /* TODO: Make sure this only works for a bool variable */
|                  '(' boolean_statement ')'
|                  '(' boolean_statement "&&" boolean_statement ')'
|                  '(' boolean_statement "||" boolean_statement ')'
|                  '(' function_call ')';             /* TODO: Make sure this only works with functions that return a boolean*/

statement: IF boolean_statement '{' statement '}'
|          ELSE '{' statement '}'
|          "return" function_call  ';'
|          "return" IDENTIFIER     ';'
|          "return" INT_LITERAL    ';'
|          "return" STR_LITERAL    ';'
|          "return" BOOL_LITERAL   ';'
|          var_definition;

%%
