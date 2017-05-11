#include "Client.h"

using namespace std;

// Se connecter au simulateur CodinGame en utilisant un exécutable comme joueur
//	argv[1] : chemin vers l'exécutable joueur
//	argv[2] : adresse IP du simulateur CodinGame
//	argv[3] : port du simulateur CodinGame
int main(int argc, char *argv[]){
	Client client;
	client.OuvrirTCP(argv[2], stoi(argv[3]));
	client.OuvrirPipes(argv[1]);
	return 1;
}

Client::Client(){
	connected = false;
}

void Client::OuvrirTCP(const char* ip, int port){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		cout << "Échec ouverture socket client " + string(ip) + ":" + to_string(port) << endl;
		return;
	}
	struct hostent *hostinfo = gethostbyname(ip);
	if(hostinfo == NULL){
		cout << "Échec reconnaissance serveur " + string(ip) << endl;
		return;
	}
	sockaddr_in sin = { 0 };
	sin.sin_family = AF_INET;
	sin.sin_addr = *(in_addr*) hostinfo->h_addr;
	sin.sin_port = htons(port);
	if(connect(sock,(sockaddr*) &sin, sizeof(sockaddr)) < 0){
		cout << "Échec connexion socket client " + string(ip) + ":" + to_string(port) << endl;
		return;
	}
	connected = true;
	return;
}

void Client::OuvrirPipes(const char* executablePath){
	if(!connected){return;}
	if(pipe(pipeIn) == -1 || pipe(pipeOut) == -1){
		cerr << "Echec création pipes" << endl;
		return;
	}
	pid = fork();
	if(pid == 0){
		close(fileno(stdin));
		close(fileno(stdout));
		dup2(pipeIn[0], fileno(stdin));
		dup2(pipeOut[1], fileno(stdout));
		close(pipeIn[1]);
		close(pipeOut[0]);
		execl(executablePath, executablePath, (void *) NULL);
	}
	else{
		close(pipeIn[0]);
		close(pipeOut[1]);
		pid = fork();
		if(pid == 0){
			PipeToTCPLoop();
		}
		else{
			TCPToPipeLoop();
		}
	}
}

void Client::PipeToTCPLoop(){
	char buffer[1024];
	while(connected){
		size_t inputSize = read(pipeOut[0], buffer, sizeof(buffer));
		send(sock, buffer, inputSize, 0);
	}
}

void Client::TCPToPipeLoop(){
	char buffer[1024];
	while(connected){
		size_t inputSize = recv(sock, buffer, 1024, 0);
		size_t outputSize = write(pipeIn[1], buffer, inputSize);
		if(inputSize == 0 || outputSize == 0){
			connected = false;
		}
	}
}
