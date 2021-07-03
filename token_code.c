#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "token_code.h"

size_t count_tokens(char *input, size_t input_length){
 size_t token_count = 0;
 for(size_t i = 0; i < input_length; i++){
  if((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_'){
   while((i < input_length) && ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_')){
    i++;
   }
   token_count++;
   i--;
  }
  switch(input[i]){
   case ':':
    token_count++;
    break;
   case ';':
    token_count++;
    break;
   case '.':
    token_count++;
    break;
   case '\"':
    token_count++;
    break;
   case '-':
    token_count++;
    break;
   case '(':
    token_count++;
    break;
   case ')':
    token_count++;
    break;
   case '<':
    token_count++;
    break;
   case '>':
    token_count++;
    break;
   case '[':
    token_count++;
    break;
   case ']':
    token_count++;
    break;
   case '{':
    token_count++;
    break;
   case '}':
    token_count++;
    break;
   case '=':
    token_count++;
    break;
   case '&':
    token_count++;
    break;
   case '|':
    token_count++;
    break;
   case '!':
    token_count++;
    break;
   case ',':
    token_count++;
    break;
   case '*':
    token_count++;
    break;
   case '+':
    token_count++;
    break;
   default:
    break;
  }
 }

 return token_count;
}

void getTokenStart(char *input, size_t input_length, size_t *token_start){
 size_t token_index = 0;
 for(size_t i = 0; i < input_length; i++){
  if((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_'){
   token_start[token_index] = i;
   while((i < input_length) && ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_')){
    i++;
   }
   token_index++;
   i--;
  }
  switch(input[i]){
   case ':':
    token_start[token_index] = i;
    token_index++;
    break;
   case ';':
    token_start[token_index] = i;
    token_index++;
    break;
   case '.':
    token_start[token_index] = i;
    token_index++;
    break;
   case '\"':
    token_start[token_index] = i;
    token_index++;
    break;
   case '-':
    token_start[token_index] = i;
    token_index++;
    break;
   case '(':
    token_start[token_index] = i;
    token_index++;
    break;
   case ')':
    token_start[token_index] = i;
    token_index++;
    break;
   case '<':
    token_start[token_index] = i;
    token_index++;
    break;
   case '>':
    token_start[token_index] = i;
    token_index++;
    break;
   case '[':
    token_start[token_index] = i;
    token_index++;
    break;
   case ']':
    token_start[token_index] = i;
    token_index++;
    break;
   case '{':
    token_start[token_index] = i;
    token_index++;
    break;
   case '}':
    token_start[token_index] = i;
    token_index++;
    break;
   case '=':
    token_start[token_index] = i;
    token_index++;
    break;
   case '&':
    token_start[token_index] = i;
    token_index++;
    break;
   case '|':
    token_start[token_index] = i;
    token_index++;
    break;
   case '!':
    token_start[token_index] = i;
    token_index++;
    break;
   case ',':
    token_start[token_index] = i;
    token_index++;
    break;
   case '*':
    token_start[token_index] = i;
    token_index++;
    break;
   case '+':
    token_start[token_index] = i;
    token_index++;
    break;
   default:
    break;
  }
 }
}

void getTokenEnd(char *input, size_t input_length, size_t *token_end){
 size_t token_index = 0;
 for(size_t i = 0; i < input_length; i++){
  if((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_'){
   while((i < input_length) && ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_')){
    i++;
   }
   token_end[token_index] = i;
   token_index++;
   i--;
  }
  switch(input[i]){
   case ':':
    token_end[token_index] = i;
    token_index++;
    break;
   case ';':
    token_end[token_index] = i;
    token_index++;
    break;
   case '.':
    token_end[token_index] = i;
    token_index++;
    break;
   case '\"':
    token_end[token_index] = i;
    token_index++;
    break;
   case '-':
    token_end[token_index] = i;
    token_index++;
    break;
   case '(':
    token_end[token_index] = i;
    token_index++;
    break;
   case ')':
    token_end[token_index] = i;
    token_index++;
    break;
   case '<':
    token_end[token_index] = i;
    token_index++;
    break;
   case '>':
    token_end[token_index] = i;
    token_index++;
    break;
   case '[':
    token_end[token_index] = i;
    token_index++;
    break;
   case ']':
    token_end[token_index] = i;
    token_index++;
    break;
   case '{':
    token_end[token_index] = i;
    token_index++;
    break;
   case '}':
    token_end[token_index] = i;
    token_index++;
    break;
   case '=':
    token_end[token_index] = i;
    token_index++;
    break;
   case '&':
    token_end[token_index] = i;
    token_index++;
    break;
   case '|':
    token_end[token_index] = i;
    token_index++;
    break;
   case '!':
    token_end[token_index] = i;
    token_index++;
    break;
   case ',':
    token_end[token_index] = i;
    token_index++;
    break;
   case '*':
    token_end[token_index] = i;
    token_index++;
    break;
   case '+':
    token_end[token_index] = i;
    token_index++;
    break;
   default:
    break;
  }
 }
}

size_t getTokenInitialType(char *input, size_t token_start, size_t token_end){
 if(token_start == token_end){
  switch(input[token_start]){
   case ':':
    return COLON;
    break;
   case ';':
    return SEMICOLON;
    break;
   case '.':
    return DOT;
    break;
   case '\"':
    return QUOTES;
    break;
   case '-':
    return DASH;
    break;
   case '(':
    return OPEN_PARENTHESES;
    break;
   case ')':
    return CLOSE_PARENTHESES;
    break;
   case '<':
    return OPEN_CARROT;
    break;
   case '>':
    return CLOSE_CARROT;
    break;
   case '[':
    return OPEN_SQUARE;
    break;
   case ']':
    return CLOSE_SQUARE;
    break;
   case '{':
    return OPEN_CURLY;
    break;
   case '}':
    return CLOSE_CURLY;
    break;
   case '=':
    return EQUALS_SIGN;
    break;
   case '&':
    return AND;
    break;
   case '|':
    return OR;
    break;
   case '!':
    return NOT;
    break;
   case ',':
    return COMMA;
    break;
   case '*':
    return STAR;
    break;
   case '+':
    return PLUS;
    break;
   default:
    break;
  } 
 } else{
  size_t length = token_end - token_start;
  if((length >= 2) && (length <= 5)){
   switch(input[token_start]){
    case 'i':
     if(length == 2){
      if(strncmp(input + token_start, "if", 2) == 0){
       return IF;
      }
     }else if(length == 3){
      if(strncmp(input + token_start, "int", 3) == 0){
       return INT_DECLARATION;
      }
     }
     break;
    case 'e':
     if(length == 4){
      if(strncmp(input + token_start, "else", 4) == 0){
       return ELSE;
      }
     }
     break;
    case 's':
     if(length == 3){
      if(strncmp(input + token_start, "str", 3) == 0){
       return STR_DECLARATION;
      }
     }
     break;
    case 'b':
     if(length == 4){
      if(strncmp(input + token_start, "bool", 4) == 0){
       return BOOL_DECLARATION;
      }
     }
     break;
    case 'f':
     if(length == 4){
      if(strncmp(input + token_start, "func", 4) == 0){
       return FUNCTION_DECLARATION;
      }
     }else{
      if(length == 5){
       if(strncmp(input + token_start, "false", 5) == 0){
        return BOOL_LITERAL;
       }
      }
     }
     break;
    case 'l':
     if(length == 3){
      if(strncmp(input + token_start, "let", 3) == 0){
       return LET;
      }
     }
     break;
    case 't':
     if(length == 4){
      if(strncmp(input + token_start, "true", 4) == 0){
       return BOOL_LITERAL;
      }
     }
     break;
   }
  }
 }
 if(input[token_start] >= '0' && input[token_start] <= '9'){
  return INT_LITERAL;
 }
 return OTHER;
}

