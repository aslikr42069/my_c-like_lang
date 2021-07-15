#include "Lexer.h"

void lexIdentifier(char *input, size_t input_size, size_t *index){
 while((*index < input_size-1) && ((input[*index] >= 'A' && input[*index] <= 'Z') || (input[*index] >= 'a' && input[*index] <= 'z') || (input[*index] == '_'))){
  *index += 1;
 }
}

void lexStringLiteral(char *input, size_t input_size, size_t *index){
 while((*index < input_size-1) && (input[*index] != '\"')){
  if(input[*index] == '\\'){
   if(*index + 1 < input_size - 1){
    if(input[*index + 1] == '\"'){
     *index += 1;
    }
   }
  }
  *index += 1;
 } 
 *index += 1;
}

void lexSingleLineComment(char *input, size_t input_size, size_t *index){
 size_t tmp = *index;
 while((tmp < input_size - 1) && (input[tmp] != '\n')){
  tmp++;
 }
 *index = tmp;
}

void lexMultiLineComment(char *input, size_t input_size, size_t *index){
 size_t tmp = *index;
 while((tmp < input_size - 1)){
  if(input[tmp] == '*'){
   if(tmp + 1 < input_size - 1){
    if(input[tmp + 1] == '/'){
     tmp++;
     break;
    }
   }
  }
  tmp++;
 }
 tmp++;
 *index = tmp;
}

void lexCharLiteral(char *input, size_t input_size, size_t *index){
 size_t tmp = *index;
 while(input[tmp] != '\''){
  if(input[tmp] == '\\'){
   if(tmp + 1 < input_size - 1){
    if((input[tmp + 1] == '\'') || (input[tmp + 1] == '\\') || (input[tmp + 1] == 'n') || (input[tmp + 1] == 't')){
     tmp += 1;
    } else {
     printf("Unknown escape sequence \\%c\n", input[tmp+1]);
     exit(1);
    }
   }
  }
 tmp += 1;
 }
 tmp += 1;
 *index = tmp;
}

void lexHexNumber(char *input, size_t input_size, size_t *index){
 size_t tmp = *index;
 while((tmp < input_size-1) && ((input[tmp] >= '0' && input[tmp] <= '9') || (input[tmp] >= 'A' && input[tmp] <= 'F') || (input[tmp] >= 'a' && input[tmp] <= 'f') )){
  tmp++;
 }
 *index = tmp;
}

void lexBinNumber(char *input, size_t input_size, size_t *index){
 size_t tmp = *index;
 while((tmp < input_size-1) && (input[tmp] == '0' || input[tmp] == '1')){
  tmp++;
 }
 *index = tmp;
}

void lexDecNumber(char *input, size_t input_size, size_t *index){
 while((*index < input_size-1) && (input[*index] >= '0' && input[*index] <= '9')){
  *index += 1;
 }
}

void lexPositiveNumber(char *input, size_t input_size, size_t *index){
 size_t state = 0;
 if(input[*index] == '0'){
  if((*index) + 2 < input_size-1){
   char next_char = input[*index + 1];
   switch(next_char){
    case 'x':
     state = 0; // It's a hex number, lexicaly analyze the hex number :)
     break;
    case 'b':
     state = 1; // It's a binary number
     break;
    case '0':
     state = 2;
     break;
    case '1':
     state = 2;
     break;
    case '2':
     state = 2;
     break;
    case '3':
     state = 2;
     break;
    case '4':
     state = 2;
     break;
    case '5':
     state = 2;
     break;
    case '6':
     state = 2;
     break;
    case '7':
     state = 2;
     break;
    case '8':
     state = 2;
     break;
    case '9':
     state = 2;
     break;
    default:
     state = 3; // It's not a number or hex or binary
     break;
   }
   *index += 2;
  } else{
   return;
  }
 } else {
  if(input[*index] >= '1' && input[*index] <= '9'){
   state = 2;
  } else {
   state = 3;
  }
 }
 switch(state){
  case 0: /* Hex   */
   lexHexNumber(input, input_size, index); 
   printf("Found Hexadecimal Number\n");
   break;
  case 1: /* Bin   */
   lexBinNumber(input, input_size, index);
   printf("Found Binary Number\n");
   break;
  case 2: /* Dec   */
   lexDecNumber(input, input_size, index);
   printf("Found Decimal Number\n");
   break;
  case 3: /* Other */
   return;
   break;
 } 
}

size_t lex(char *input, size_t input_size, size_t *index){
 if(input[*index] == ' ' || input[*index] == '\n' || input[*index] == '\t'){
  size_t tmp = *index;
  while(input[tmp] == ' ' || input[tmp] == '\n' || input[tmp] == '\t'){
   tmp++;
  }
  *index = tmp;
 }
 if((input[*index] >= 'A' && input[*index] <= 'Z') || (input[*index] >= 'a' && input[*index] <= 'z') || (input[*index] == '_')){
  /* if a token starts with [_A-Za-z], then it is an identifier. That's how we define it,
     and this is what is run when a token that starts off with [_A-Za-z] is identified :))*/
  if(input_size == ((*index) + 1)){
   printf("Found Identifier\n");
   return IDENTIFIER;
  }
  lexIdentifier(input, input_size, index);
  printf("Found Identifier\n");
  return IDENTIFIER;
 } else if((input[*index] >= '0' && input[*index] <= '9')){
  /* This will be used for handling non-negative numbers. Just splitting it up makes our lives somewhat easier */
  lexPositiveNumber(input, input_size, index);
  return INT_LITERAL;
 } else if(input[*index] == '-'){ /* This handles the - sign, which is a complicated thing to deal with */
  if(*index+1 < input_size-1){
   if(input[*index + 1] == '>'){
    *index += 2;
    printf("Found Arrow\n");
    return ARROW;
   } else if((input[*index + 1] >= '0' && input[*index + 1] <= '9')){
     *index += 1;
     lexPositiveNumber(input, input_size, index);
     printf("Found negative number\n");
     return INT_LITERAL;
    } else {
    printf("Detected Minus sign\n");
    *index += 1;
    return MINUS;
   }
   *index += 2;
  } else {
   *index += 1;
   printf("Detected Minus sign\n");
   return MINUS;
  }
 } else if(input[*index] == '\"'){
  /* This code will handle string literals */
  *index += 1;
  lexStringLiteral(input, input_size, index);
  printf("Found str literal\n");
  return STR_LITERAL; 
 } else if(input[*index] == '\''){
   *index += 1;
   lexCharLiteral(input, input_size, index);
   printf("Found Char Literal\n");
   return CHAR_LITERAL;
  } else if(input[*index] == '/'){
   if((*index + 1 < input_size - 1) && (input[*index + 1] == '/' || input[*index + 1] == '*')){
    if(input[*index + 1] == '/'){
     lexSingleLineComment(input, input_size, index);
     printf("Found Single Line Comment\n");
    }else{
     lexMultiLineComment(input, input_size, index);
     printf("Found Multi Line Comment\n");
    }
   } else {
    printf("Found division symbol\n"); 
    return DIVIDE;
   }
  } else {
   switch(input[*index]){
    case '+':
     *index += 1;
     return PLUS;
     break;
    case '*':
     *index += 1;
     return TIMES;
     break;
    case '&':
     *index += 1;
     return AND;
     break;
    case '|':
     *index += 1;
     return OR;
     break;
    case '(':
     *index += 1;
     return LEFT_PAREN;
     break;
    case ')':
     *index += 1;
     return RIGHT_PAREN;
     break;
    case '[':
     *index += 1;
     return LEFT_SQUARE;
     break;
    case ']':
     *index += 1;
     return RIGHT_SQUARE;
     break;
    case '{':
     *index += 1;
     return LEFT_CURLY;
     break;
    case '}':
     *index += 1;
     return RIGHT_CURLY;
     break; 
    default:
     *index += 1;
     printf("Found OTHER\n");
     return OTHER;
     break;
   } 
 }
}
