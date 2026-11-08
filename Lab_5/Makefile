CC = gcc
CFLAGS = -std=c11 -D_POSIX_C_SOURCE=200112L
PROGRAM = main.out
SOURCE = getaddress.c

build:
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCE)

clean:
	rm -f $(PROGRAM)

run:
	./$(PROGRAM) $(A)
        