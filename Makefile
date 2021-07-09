CC      = gcc
CFLAGS  = -O2 -std=c11 -Wall -Wextra -Wpedantic -march=native -lfl -pipe
INFILES = main.c Lexer.c Parser.c
OUTFILE = language

default: Lexer.c Parser.c
	$(CC) $(CFLAGS) $(INFILES) -o $(OUTFILE)

Lexer.c: funlang.l
	flex -Cf -B funlang.l

Parser.c: Lexer.c funlang.y
	bison -d -Wcounterexamples funlang.y
clean:
	rm Lexer.* Parser.* $(OUTFILE)
