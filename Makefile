CC=g++
WINCC=wineg++
CFLAGS=-Wall -Wextra -std=c++20 -O3
LIBS=-lraylib

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp $(LIBS)
	$(WINCC) $(CFLAGS) -o main main.cpp $(LIBS)

clean:
	rm -f main
	rm -f main.exe main.exe.so
