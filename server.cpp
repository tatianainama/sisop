
void inicializarMemoriaCompartida();
#include "server.h"
#include "network.cpp"


 

int main(int argc, char ** argv){
	Timer fps;
	Engine eng;
	std::string remoteCommandP1, remoteCommandP2;
	std::istringstream temp;
	int command;
	int confd1, confd2; 
	Network n;
	int sockfd = n.nsocket();

	std::cout << "PARAMS\n" << argc;

	if(argc < 1){
		
		t_partida p;
		inicializarMemoriaCompartida();
		fflush(stdout);
		printf("SERVIDOR PARTIDA \n");
		printf("SERVIDOR PARTIDA2 \n");
		printf("SERVIDOR PARTIDA3 \n");
		printf("NOM: %s\n",partidaMC->jugador1.nombre);
		printf("SERVIDOR PARTIDA3-b \n");
		fflush(stdout);

		printf("SERVIDOR PARTIDA4 \n");
		p = *partidaMC;
		confd1 = p.jugador1.socket;
		confd2 = p.jugador2.socket;
		printf("Socket 1: %d - %s | Socket 2: %d - %s\n", p.jugador1.socket, p.jugador1.nombre, p.jugador2.socket, p.jugador2.nombre);
		//printf("Socket 1: %d - %s | Socket 2: %d - %s\n", p.jugador1.socket, p.jugador1.nombre, p.jugador2.socket, p.jugador2.nombre);
		
	} else{

		int sockfd = n.nsocket();
		std::cout << "server";	
		fflush(stdout);

		n.nlisten(sockfd,atoi(argv[1]));
		confd1 = n.naccept(sockfd);
		confd2 = n.naccept(sockfd);

	  std::cout << n.nreceive(confd1);
	  std::cout << n.nreceive(confd2);

	  n.nsend(confd1,"pepe");
	  n.nsend(confd2,"pepe");
	}




	


	printf("SERVIDOR PARTIDA5 \n");


    int i = 1;
    //setsockopt( confd1, IPPROTO_TCP, TCP_NODELAY, (void *)&i, sizeof(i));
    //setsockopt( confd2, IPPROTO_TCP, TCP_NODELAY, (void *)&i, sizeof(i));

	printf("SERVIDOR PARTIDA6 \n");
	//printf("Socket 1: %d - %s | Socket 2: %d - %s\n", p.jugador1.socket, p.jugador1.nombre, p.jugador2.socket, p.jugador2.nombre);


  	std::cout << "Accepted\n";

/*
	// Test if the socket is in non-blocking mode:
	if(fcntl(confd1, F_GETFL) & O_NONBLOCK) {
	    // socket is non-blocking
	      std::cout << "*****socket1 is non-blocking*****\n";
	}else{
		  std::cout << "*****socket1 BLOCKS*****\n";	
	}

	// Put the socket in non-blocking mode:
	if(fcntl(confd1, F_SETFL, fcntl(confd1, F_GETFL) | O_NONBLOCK) < 0) {
	    // handle error
	    std::cout << "*****error settinh socket1 non-blocking*****\n";
	}else {
		std::cout << "*****OK setting socket1 non-blocking OK*****\n";
	}

	// Test if the socket is in non-blocking mode:
	if(fcntl(confd2, F_GETFL) & O_NONBLOCK) {
	    // socket is non-blocking
	      std::cout << "*****socket2 is non-blocking*****\n";
	}else{
		  std::cout << "*****socket2 BLOCKS*****\n";	
	}

	// Put the socket in non-blocking mode:
	if(fcntl(confd2, F_SETFL, fcntl(confd2, F_GETFL) | O_NONBLOCK) < 0) {
	    // handle error
	    std::cout << "*****error settinh socket2 non-blocking*****\n";
	}else {
		std::cout << "*****OK setting socket2 non-blocking OK*****\n";
	}
*/


	while (!eng.done) {
        //Start the frame timer
        fps.start();

        //eng.capturekeys();

        eng.update();
	    		
        eng.afterUpdate();
	printf("SERVIDOR PARTIDA7 \n");	    
        //eng.render();

  	    //std::cout << eng.gameStateToString();
  	    //std::cout << "tamano" << eng.gameStateToString().length();  	    

	    eng.applyCommand(remoteCommandP1,1);	    
	    eng.applyCommand(remoteCommandP2,2);

		printf("SERVIDOR PARTIDA8 \n");
	    remoteCommandP1 = "";
	   	remoteCommandP2 = "";

	   	n.nsend(confd1,eng.gameStateToString());
  	  n.nsend(confd2,eng.gameStateToString());
  	      std::cout << "ya envie estado----------------\n";
	    //Cap the frame rate

	    std::cout << "hago recv de comandos remotos----------------\n";
	   	remoteCommandP1 = n.nreceive(confd1);
	    remoteCommandP2 = n.nreceive(confd2);
	    if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
	        SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks());
	    }

	}//end game loop

    eng.free();

    printf("Exited cleanly\n");
    return 0;
}



void inicializarMemoriaCompartida()
{
	//Inicializo la memoria compartida y los semáforos correspondientes, al igual que en el server del torneo pero con el pid del padre, para que se llamen igual.
	printf("Inicializando memoria compartida\n");
	fflush(stdout);
	int pidInt = getppid(), fd;
	char pid[6];
	sprintf(pid, "%d", pidInt);
	strcat(shmName, pid);
	printf("SHMNAME: %s\n", shmName);
	fflush(stdout);
	if( ( fd = shm_open(shmName, O_RDWR, 0777 ) ) < 0 )
	{
		printf("Error abriendo la memoria compartida.\n");
		fflush(stdout);
		exit(1);
	}

	if(ftruncate(fd, sizeof(t_partida)) == -1)
	{
		printf("Error estableciendo el tamaño.\n");
		fflush(stdout);
		exit(1);
	}
	partidaMC = (t_partida *) mmap(0, sizeof(t_partida), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if(partidaMC == MAP_FAILED)
	{
		printf("Error mapeando a memoria.\n");
		fflush(stdout);
		exit(1);
	}

	// Se utilizan los mismos nombres del servidor para los semáforos
	strcat(semEscrituraPath, pid);
	strcat(semLecturaPath, pid);
	semEscritura = sem_open( semEscrituraPath, O_CREAT, 0777);
	semLectura = sem_open( semLecturaPath, O_CREAT, 0777);

	sprintf(pid, "%d", getpid());
	//strcat(semStartName, pid);
}
