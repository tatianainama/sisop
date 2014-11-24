#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <poll.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <netinet/tcp.h>

#define MAX_CONEX 20
#define MAX_PART 10
#define TAMBUF 255
#define J1 0
#define J2 1
//#define _GNU_SOURCE

///// ESTADOS
#define ACTIVO 2
#define DESCONECTADO -2
#define VACIO -1
#define LIBRE 0
#define GANADOR 7
#define JUGANDO 3

#define LARGO_PANTALLA 800
#define ALTO_PANTALLA 600
#define BPP 32
#define INICIO_TABLERO 200
#define FUERADEMAPA 630


///////////////Estructuras///////////////
typedef struct { 
	//Estructura de clientes
	int orden;
	int socket;
	char nombre[255];
	int estado;
	int puntaje;
	int rescates;
	int vidas;
	int cantPartidasGanadas;
}  t_jugador;

typedef struct {
	t_jugador vec[MAX_CONEX];
	int tam;
}  t_vec_jugadores;

typedef struct { 
	//Estructura de partida.
	t_jugador jugador1;
	t_jugador jugador2;
	int ganador;
	int puntaje1;
	int puntaje2;
	pid_t pid;
	int tiempo_barriles;
	int tiempo_fuegos;
}  t_partida;

typedef struct {
	t_partida vec[MAX_PART];
	int tam;
}  t_vec_partida;

typedef struct{
	int port;
	int timeOut_srv;
	int timeOut_part;
	int rescates;
	char nivel;
}  t_config_srv;

typedef struct {
	int nro_jugador;
	int socket;
	char mensaje[255];
} t_mensaje_cliente;

struct header {
	short int remitente;
	unsigned char operacion;
};

struct body {
	short int numero_jugador;
	unsigned char sprite;
	short int x;		
	short int y;
	short int h;
	short int w;
	char cad[50];
	unsigned int rescates;
	unsigned int time;
};

typedef struct mensaje {
	struct header cabecera;
	struct body cuerpo;
}mensaje;


/////////// VARIABLES ///////////////

int ganador[MAX_CONEX];
sem_t * semEscritura;
sem_t * semLectura;

char semEscrituraPath[30]="/semEscritura";
char semLecturaPath[30]="/semLectura";
char shmName[30]="/shMemory";

t_partida * partidaMC;
