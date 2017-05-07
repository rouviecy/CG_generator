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
	void OuvrirTCP(const char* ip, int port);
	void OuvrirPipes();

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
