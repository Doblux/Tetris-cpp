CC=g++
CFLAGS=-Wall -Wextra -std=c++20
LIBS=-lraylib

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp $(LIBS) && ./main

clean:
	rm -f main
