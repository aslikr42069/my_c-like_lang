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

array_list: INT_LITERAL
|           IDENTIFIER
|           indexing_expression
|           STR_LITERAL
|           BOOL_LITERAL
|           array_list ',' IDENTIFIER
|           array_list ',' indexing_expression
|           array_list ',' INT_LITERAL
|           array_list ',' STR_LITERAL
|           array_list ',' BOOL_LITERAL;


var_definition: INT_KEYWORD IDENTIFIER '=' INT_LITERAL ';'
|               INT_KEYWORD IDENTIFIER ';'
|               INT_KEYWORD indexing_expression '=' array_list ';'
|               INT_KEYWORD indexing_expression ';'
|               STR_KEYWORD IDENTIFIER '=' STR_LITERAL ';'
|               STR_KEYWORD IDENTIFIER ';'
|               STR_KEYWORD indexing_expression '=' array_list ';'
|               STR_KEYWORD indexing_expression ';'
|               BOOL_KEYWORD IDENTIFIER '=' BOOL_LITERAL ';'
|               BOOL_KEYWORD IDENTIFIER ';'
|               BOOL_KEYWORD indexing_expression '=' array_list ';'
|               BOOL_KEYWORD indexing_expression ';';


function_call: IDENTIFIER '(' call_parameters ')';

boolean_statement: '(' IDENTIFIER "==" IDENTIFIER ')' /* TODO: Make sure this only works for ints */
|                  '(' IDENTIFIER ')'                 /* TODO: Make sure this only works for a bool variable */
|                  '(' indexing_expression ')'        /* TODO: Make sure the array that is being indexed is of type bool */
|                  '(' boolean_statement ')'
|                  '(' boolean_statement "&&" boolean_statement ')'
|                  '(' boolean_statement "||" boolean_statement ')'
|                  '(' '!' boolean_statement ')'
|                  '(' function_call ')';             /* TODO: Make sure this only works with functions that return a boolean*/

BINARY_OPERATOR: '+'| '-' | '*' | '/' | '&' | '|';

math_expression: '(' BINARY_OPERATOR INT_LITERAL       INT_LITERAL         ')'
|                '(' BINARY_OPERATOR INT_LITERAL       IDENTIFIER          ')'
|                '(' BINARY_OPERATOR IDENTIFIER        INT_LITERAL         ')'
|                '(' BINARY_OPERATOR INT_LITERAL       function_call       ')'
|                '(' BINARY_OPERATOR function_call     INT_LITERAL         ')'
|                '(' BINARY_OPERATOR function_call     function_call       ')'
|                '(' BINARY_OPERATOR INT_LITERAL       math_expression     ')'
|                '(' BINARY_OPERATOR math_expression   INT_LITERAL         ')'
|                '(' BINARY_OPERATOR math_expression   IDENTIFIER          ')'
|                '(' BINARY_OPERATOR IDENTIFIER        math_expression     ')'
|                '(' BINARY_OPERATOR math_expression   function_call       ')'
|                '(' BINARY_OPERATOR function_call     math_expression     ')'
|                '(' BINARY_OPERATOR math_expression   math_expression     ')';

indexing_expression: IDENTIFIER '[' INT_LITERAL ']'
|                    IDENTIFIER '[' IDENTIFIER  ']';  /* TODO: Make sure this identifier can only be an int variable*/

statement: IF boolean_statement '{' statement '}'
|          ELSE '{' statement '}'
|          "return" function_call  ';'
|          "return" IDENTIFIER     ';'
|          "return" INT_LITERAL    ';'
|          "return" STR_LITERAL    ';'
|          "return" BOOL_LITERAL   ';'
|          var_definition;

%%
