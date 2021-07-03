CC      = gcc
CFLAGS  = -O2 -std=c99 -Wall -Wextra -Wpedantic -march=native
INFILES = main.c token_code.c
OUTFILE = language

default:
	$(CC) $(CFLAGS) $(INFILES) -o $(OUTFILE)
