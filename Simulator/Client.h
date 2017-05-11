#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

class Client{

public:
	Client();
	void OuvrirTCP(				// Se connecter au simulateur CodinGame (Referee.java)
		const char* ip,				// Adresse IP du serveur
		int port);				// Port du serveur
	void OuvrirPipes(			// Se connecter à l'exécutable joueur
		const char* executablePath);		// Chemin vers l'exécutable

private:
	pid_t pid;
	int pipeIn[2];
	int pipeOut[2];
	bool connected;
	int sock;
	void TCPToPipeLoop();
	void PipeToTCPLoop();
};

#endif
