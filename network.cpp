#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h> 
#include <pthread.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

class Network {

	public:
	int nsocket();
	void nlisten(int,int);

	int nconnect(int, std::string, int);
	int naccept(int);

	void nsend(int, std::string);
	std::string nreceive(int);

};


int Network::nconnect(int sockfd, std::string Adress, int port){

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, Adress.c_str(), &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error\n");
        return 1;
    }

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Conectando \n");
       return 1;
    } 
    int i = 1;
    setsockopt( sockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&i, sizeof(i));

	std::cout << "conectando " << Adress << ":" << port << "\n";
};

int Network::naccept(int listenfd){
	int m = 1;
	int connfd;
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    setsockopt( connfd, IPPROTO_TCP, TCP_NODELAY, (void *)&m, sizeof(m));  

    return connfd;          
};

void Network::nlisten(int listenfd,int port){

    struct sockaddr_in serv_addr; 

    //listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    //int port = 4545;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10);
    //return listenfd;
};

void Network::nsend(int connfd, std::string mens){

	std::cout << "\ntamaño original: " << mens.length() << "\n";
	int tam = 200, flags = 0;
	char recBuff[tam];
	memset(&recBuff, '1', sizeof(recBuff));	
	strcpy(recBuff,mens.c_str());
	printf("enviando men:\n%s",recBuff);
	
	std::cout << "\nhago sen de tamanio " << sizeof(recBuff) << "\n";

	send(connfd, recBuff, tam,0);
	std::cout << "Envio ok\n";
};


std::string Network::nreceive(int connfd){

	int flags = 0;
	char  buf[200];
	memset(&buf, '0', sizeof(buf));
	size_t toread = 200;
	char  * bufptr =  &buf[0];
	
	//std::cout << "Recibiendo men";
	while (toread > 0)
	{
        ssize_t rsz = recv(connfd, buf, toread, flags);
        if (rsz <= 0){
            //return rsz;  // Error or other end closed cnnection 
        }

        toread -= rsz;  // Read less next time 
        bufptr += rsz;  // Next buffer position to read into 
        //printf("Mensaje::: %ld",toread);
        //std::cout << "toRead: " << toread << "\n";
	}
	//printf("Mensaje::: %s",buf);

	//std::cout << "Mensaje Recibido :::" << buf << "\n";
	return std::string(buf);
};

int Network::nsocket(){
	int sockfd;
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        return -1;
    }

    return sockfd;
};

/*
int main(int argc, char *argv[]) {

	Network n;
	int sockfd = n.nsocket();

	if(argc == 2) {		
		std::cout << "cliente";

		n.nconnect(sockfd,"127.0.0.1",4545);
		n.nsend(sockfd,"pepepepep");

	} else {
		std::cout << "server";

		n.nlisten(sockfd);
		fflush(stdout);

		int confd = n.naccept(sockfd);
		n.nreceive(confd);
	}

}
*/



