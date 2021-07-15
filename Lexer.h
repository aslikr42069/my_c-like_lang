#ifndef _LEXER_DOT_H
#define _LEXER_DOT_H 1

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

enum TOKEN_TYPE{IDENTIFIER, INT_LITERAL, STR_LITERAL, CHAR_LITERAL, PLUS, MINUS, TIMES, DIVIDE, AND, OR, LEFT_PAREN, RIGHT_PAREN,
                LEFT_SQUARE, RIGHT_SQUARE, LEFT_CURLY, RIGHT_CURLY, IF, ELSE, INT_KEYWORD, STR_KEYWORD, BOOL_KEYWORD,
                FUNC_KEYWORD, ARROW, OTHER};

void lexIdentifier(char *input, size_t input_size, size_t *index);
void lexStringLiteral(char *input, size_t input_size, size_t *index);
void lexSingleLineComment(char *input, size_t input_size, size_t *index);
void lexMultiLineComment(char *input, size_t input_size, size_t *index);
void lexCharLiteral(char *input, size_t input_size, size_t *index);
void lexHexNumber(char *input, size_t input_size, size_t *index);
void lexBinNumber(char *input, size_t input_size, size_t *index);
void lexDecNumber(char *input, size_t input_size, size_t *index);
void lexPositiveNumber(char *input, size_t input_size, size_t *index);
size_t lex(char *input, size_t input_size, size_t *index);


#endif
