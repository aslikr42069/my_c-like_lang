%define api.pure full
%locations
%param {yyscan_t scanner}

%{
 #include <stdio.h>
 #include <stdint.h>
 #include "abstract_tree.h"

 ASTnode_t *makeNode(enum AST_NODES_TYPE type, size_t child_count, char *name, intmax_t value);
%}

%code requires{
 typedef void* yyscan_t;
}

%code{
 int yylex(YYSTYPE* yylvalp, YYLTYPE* yyllocp, yyscan_t scanner);
}


%token FUNCTION_KEYWORD IF ELSE INT_KEYWORD STR_KEYWORD BOOL_KEYWORD ARROW
%token BOOL_LITERAL STR_LITERAL CHAR_LITERAL COMMENT WHILE OTHER
%token <val>  INT_LITERAL
%token <name> IDENTIFIER

%output  "Parser.c"
%defines "Parser.h"

%union{
 char *name;
 intmax_t val;
 struct ASTnode_t *node; 
};


%%

program: program function
|        function;

function: FUNCTION_KEYWORD IDENTIFIER '(' parameters ')' ARROW INT_KEYWORD  '{' statements '}'
|         FUNCTION_KEYWORD IDENTIFIER '(' parameters ')' ARROW STR_KEYWORD  '{' statements '}'
|         FUNCTION_KEYWORD IDENTIFIER '(' parameters ')' ARROW BOOL_KEYWORD '{' statements '}';

statements: statements statement
|           %empty;

parameters: parameter
|           %empty;

parameter: INT_KEYWORD                IDENTIFIER
|          parameter ',' INT_KEYWORD  IDENTIFIER
|          STR_KEYWORD                IDENTIFIER
|          parameter ',' STR_KEYWORD  IDENTIFIER
|          BOOL_KEYWORD               IDENTIFIER
|          parameter ',' BOOL_KEYWORD IDENTIFIER;

call_parameters: call_parameter
|                %empty;


call_parameter: IDENTIFIER
|               INT_LITERAL
|               STR_LITERAL
|               BOOL_LITERAL
|               boolean_statement
|               call_parameter ',' IDENTIFIER
|               call_parameter ',' INT_LITERAL
|               call_parameter ',' STR_LITERAL
|               call_parameter ',' BOOL_LITERAL
|               call_parameter ',' boolean_statement;

array_list: INT_LITERAL
|           IDENTIFIER
|           function_call
|           indexing_expression
|           STR_LITERAL
|           BOOL_LITERAL
|           array_list ',' IDENTIFIER
|           array_list ',' function_call
|           array_list ',' indexing_expression
|           array_list ',' INT_LITERAL
|           array_list ',' STR_LITERAL
|           array_list ',' BOOL_LITERAL;


immutable_var_definition: INT_KEYWORD   var_assignment
|                         STR_KEYWORD   var_assignment
|                         BOOL_KEYWORD  var_assignment
|                         INT_KEYWORD   IDENTIFIER              ';'
|                         STR_KEYWORD   IDENTIFIER              ';'
|                         BOOL_KEYWORD  IDENTIFIER              ';'
|                         INT_KEYWORD   indexing_expression     ';'
|                         STR_KEYWORD   indexing_expression     ';'
|                         BOOL_KEYWORD  indexing_expression     ';';

mutable_var_definition: "mut" immutable_var_definition;

function_call: IDENTIFIER '(' call_parameters ')';

boolean_statement: '(' IDENTIFIER "==" IDENTIFIER ')'
|                  '(' IDENTIFIER ')'               
|                  '(' IDENTIFIER '>' IDENTIFIER  ')'
|                  '(' IDENTIFIER '<' IDENTIFIER  ')'
|                  '(' IDENTIFIER ">=" IDENTIFIER ')'
|                  '(' IDENTIFIER "<=" IDENTIFIER ')'
|                  '(' indexing_expression ')'     
|                  '(' boolean_statement ')'
|                  '(' boolean_statement "&&" boolean_statement ')'
|                  '(' boolean_statement "||" boolean_statement ')'
|                  '(' '!' boolean_statement ')'
|                  '(' function_call ')';            

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
|                    IDENTIFIER '[' IDENTIFIER  ']'; 

statement: IF boolean_statement '{' statement '}'
|          ELSE '{' statement '}'
|          "return" function_call  ';'
|          "return" IDENTIFIER     ';'
|          "return" INT_LITERAL    ';'
|          "return" STR_LITERAL    ';'
|          "return" BOOL_LITERAL   ';'
|          immutable_var_definition
|          var_assignment
|          while_loop;

while_loop: WHILE boolean_statement '{' statements '}';

var_assignment: IDENTIFIER '='          STR_LITERAL          ';'
|               IDENTIFIER '='          INT_LITERAL          ';'
|               IDENTIFIER '='          BOOL_LITERAL         ';'
|               IDENTIFIER '='          function_call        ';'
|               IDENTIFIER '='          math_expression      ';'
|               indexing_expression '=' STR_LITERAL          ';'
|               indexing_expression '=' INT_LITERAL          ';'
|               indexing_expression '=' BOOL_LITERAL         ';'
|               indexing_expression '=' function_call        ';'
|               indexing_expression '=' math_expression      ';';

%%

int yyerror(char *msg){
 fprintf(stderr, "%s\n", msg);
 return 0;
}

