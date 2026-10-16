CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = $(wildcard src/*.c)

memalloc: $(SRC)
	$(CC) $(CFLAGS) -o memalloc $(SRC)

clean:
	rm -f memalloc
