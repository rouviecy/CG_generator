CC = g++
CFLAGS = -O2 -Wall -std=c++11

all: client.o test.o
	$(CC) $(CFLAGS) client.o -o client
	$(CC) $(CFLAGS) test.o -o test

client.o: Client.cpp
	$(CC) $(CFLAGS) -c Client.cpp -o client.o

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o
