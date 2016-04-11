CC=g++
CFLAGS=-g -Wall -std=c++11
OBJ=chess.o
all: main
main: main.cpp $(OBJ)
	$(CC) -o main main.cpp $(OBJ) $(CFLAGS)
chess.o: chess.cpp
	$(CC) -c -o chess.o chess.cpp $(CFLAGS)
clean:
	rm -rf *.o main
