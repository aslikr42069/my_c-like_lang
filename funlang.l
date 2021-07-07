%option outfile="Lexer.c" header-file="Lexer.h"

%option bison-bridge bison-locations never-interactive reentrant
%option warn nodefault nounistd yylineno noinput nounput
%option noyywrap batch

%{
#include <stdint.h>
#include <string.h>
#include "Parser.h"
size_t line_count = 1;
%}


int_literal        ((-)?((0x)[0-9A-Fa-f]+|[0-9]+))
str_literal        (\"(([^\"\\])|\\\"|\\\\)*\")
char_literal       (\'(.|\\n|\\\\|\\t)\')
whitespace         [ \t\r]
identifier         ([_A-Za-z])([_A-Za-z0-9]+)
controlflow        ([!#-&(-/:-@[-^{-~])
comment            ((\/\/[^\r\n]*)|(\/\*(.|[\r\n])*\*\/))


%%
"func"                {return FUNCTION_KEYWORD; }
"if"                  {return IF;               }
"else"                {return ELSE;             }
"int"                 {return INT_KEYWORD;      }
"str"                 {return STR_KEYWORD;      }
"bool"                {return BOOL_KEYWORD;     }
"true"                {return BOOL_LITERAL;     }
"false"               {return BOOL_LITERAL;     }

{int_literal}         {yylval->val = (intmax_t) strtol(yytext, (char **) NULL, 0);
                       return INT_LITERAL;      }

{str_literal}         {return STR_LITERAL;      }
"->"                  {return GIVES_TYPE;       }
{identifier}          {yylval->name = strdup(yytext);
                       return IDENTIFIER;       }
{char_literal}        {return CHAR_LITERAL;     }
{comment}             {return COMMENT;          }
\n                    {line_count++; }
{whitespace}                       ;
{controlflow}                      ;
.                     {printf("Error, unrecognized char %s at line #%li", yytext, line_count); 
                       return OTHER;            }

%%
