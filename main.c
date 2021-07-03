#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "token_code.h"

char *type_strings_printable[] = {"INT", "STRING", "BOOLEAN"};
char *type_strings_readable[] = {"int", "str", "bool"};


int main(int argc, char *argv[]){
 if(argc < 2){
  printf("%s error: No input file supplied\n", argv[0]);
  return 0;
 }
 if(argc > 3){
  printf("%s error: Too many arguments supplied\n", argv[0]);
  return 0;
 }
 FILE *file = fopen(argv[1], "r");
 if(file == NULL){
  printf("Error opening file %s\n", argv[1]);
  return 0;
 }
 fseek(file, 0, SEEK_END);
 size_t input_length = (size_t) ftell(file);
 rewind(file);
 size_t bytes_read = 0;
 char *input = (char *) malloc(sizeof(char) * input_length);
 bytes_read = fread(input, 1, input_length, file);
 if(bytes_read != input_length){
  puts("Error reading file");
  return 0;
 }
 fclose(file);
 
 size_t token_count = 0;
 token_count = count_tokens(input, input_length);
 size_t token_start[token_count];
 size_t token_end[token_count];
 getTokenStart(input, input_length, token_start);
 getTokenEnd(input, input_length, token_end);
 
 size_t tokens_types[token_count];

 for(size_t i = 0; i < token_count; i++){
  tokens_types[i] = getTokenInitialType(input, token_start[i], token_end[i]);
  printf("Token type %li = %li\n", i, tokens_types[i]);
 }

 return 0; 
}
