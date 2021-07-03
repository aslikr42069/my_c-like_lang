#ifndef TOKEN_CODE_H_
#define TOKEN_CODE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum TOKEN_TYPE{DOT, COLON, SEMICOLON, IF, ELSE, QUOTES, DASH, OPEN_PARENTHESES, CLOSE_PARENTHESES, INT_DECLARATION, BOOL_DECLARATION, STR_DECLARATION, FUNCTION_DECLARATION, OPEN_CARROT, CLOSE_CARROT, OPEN_SQUARE, CLOSE_SQUARE, OPEN_CURLY, CLOSE_CURLY, EQUALS_SIGN, LET, INT_LITERAL, BOOL_LITERAL, STRING_LITERAL, VARIABLE_CALL, FUNCTION_CALL, AND, OR, NOT, COMMA, STAR, PLUS, OTHER};

enum TYPE{INT, STRING, BOOLEAN};

size_t count_tokens(char *input, size_t input_length);
void getTokenStart(char *input, size_t input_length, size_t *token_start);
void getTokenEnd(char *input, size_t input_length, size_t *token_end);
size_t getTokenInitialType(char *input, size_t token_start, size_t token_end);

#endif
