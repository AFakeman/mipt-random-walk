CC = gcc-7
CFLAGS = -g -fopenmp -Wall -Werror

main: main.c
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -rf *.dSYM