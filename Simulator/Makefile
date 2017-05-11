CC = g++
CFLAGS = -O2 -Wall -std=c++11

all: client.o joueurIdiot.o joueurMoinsIdiot.o
	$(CC) $(CFLAGS) client.o -o client
	$(CC) $(CFLAGS) joueurIdiot.o -o joueurIdiot
	$(CC) $(CFLAGS) joueurMoinsIdiot.o -o joueurMoinsIdiot
	javac Referee.java

client.o: Client.cpp
	$(CC) $(CFLAGS) -c Client.cpp -o client.o

joueurIdiot.o: JoueurIdiot.cpp
	$(CC) $(CFLAGS) -c JoueurIdiot.cpp -o joueurIdiot.o


joueurMoinsIdiot.o: JoueurMoinsIdiot.cpp
	$(CC) $(CFLAGS) -c JoueurMoinsIdiot.cpp -o joueurMoinsIdiot.o
