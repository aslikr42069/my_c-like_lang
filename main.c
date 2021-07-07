#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "eval.h"


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
 
 YY_BUFFER_STATE state;
 yyscan_t scanner;
 yylex_init(&scanner);
 yy_scan_string(input, scanner);
 yyparse(scanner);
 yylex_destroy(scanner);
 

 free(input);
 return 0; 
}
