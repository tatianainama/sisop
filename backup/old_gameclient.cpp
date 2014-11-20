#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <stdlib.h>

#include<iostream>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "constants.h"
#include "iactor.h"
#include "timer.h"
#include "ship.h"
#include "bullet.h"
#include "fleet.h"
#include "barrier.h"
#include "bonus.h"
#include "sidebar.h"
#include "menu.h"
#include "configurationfile.h"
#include<vector>


const int FRAMES_PER_SECOND = 50;

SDL_Surface * screen;
FILE * pf;

std::vector<IActor*> actors;
Timer fps;
char recvBuff[1024];

std::string gameStateToString(std::vector<IActor*> );
void stringToGameState(std::string, std::vector<IActor*>);

void dibujar();

int juego ( int, char**);
int configuracion();
void configurar_tecla(SDLKey *,const char [30]);

int main ( int argc, char** argv )
{
//Abre el archivo de configuración
    pf = fopen("conf/configuracion.txt","rt+");
    if( pf == NULL ){
        printf("Error en la apertura del archivo de configuracion\n");
        exit(1);
	}

    printf("Inciando juego\n");
    int jugar = 0;
    int configurar = 0;
    int salir = 0;
	int test = 0;

//Inicia el modo video
    screen = SDL_SetVideoMode(900, 600, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
	
    Timer fps;
    atexit(SDL_Quit);
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
	
	SDL_WM_SetCaption("Space Battle",NULL);
    
    bool done = false;
	Menu me;
    while(!done)
    {
        fps.start();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {	
			configurar=0;
			jugar=0;
			salir=0;
			//Dispara los eventos al hacer clic en las letras
            if(me.Pressed1(event))
                jugar=1;
            if(me.Pressed2(event))
                configurar=1;
            if(me.Pressed3(event))
                salir = 1;



            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;
                break;
            } // end switch
        } // end of message processing
		
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        me.blit();

        //finally, update the screen :)
        SDL_Flip(screen);

        //Cap the frame rate
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
		
		if(test)// SIN ESTO no inicia el cliente.
			Menu me;


		if(jugar||configurar){
	
			if(jugar)
				juego(argc, argv);
				//Llama a la funcion "juego" para iniciar el juego
		 
			if(configurar)
				configuracion();
				//Llama a la funcion "configuracion" para iniciar la configuracion de teclas
		 
				screen = SDL_SetVideoMode(900, 600, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
				if ( !screen ) {
					printf("Unable to set 640x480 video: %s\n", SDL_GetError());
					return 1;
    }
		}
		
        if(salir)
            done = true;
        }
    }
    me.free();
}

int juego ( int argc, char** argv )
{
    int i = 0;
    SDLKey shoot;
    SDLKey left;
    SDLKey right;
    char ip[16];
    char line[8];
    int port;
    char movement[10];
    char movementkey[30];
    int verificacion[5];
    int fallo = 0;

    pf = fopen("conf/configuracion.txt","rt+");
    if( pf == NULL ){
        printf("Error en la apertura del archivo de configuracion\n");
        exit(1);
	}

    if( fscanf( pf, "%s", ip ) ) verificacion[0] = 1;
    fscanf( pf, "%s", line );
    if( !(port = atoi(line)) )
    {
       printf("Error. Puerto incorrecto.");
       exit(1);
    }
    else verificacion[1] = 1;

	while( i < 3)
	{
        fscanf( pf, "%s", movement );
        fscanf( pf, "%s", movementkey );
//Lee la tecla asociada al disparo
        if ((strstr( movement, "SHOOT")) != NULL ) {
            configurar_tecla(&shoot, movementkey);
            i++;
            verificacion[2] = 1;
        }
//Lee la tecla asociada al desplazamiento hacia la izquierda
        else if ((strstr("LEFT", movement)) != NULL) {
            configurar_tecla(&left, movementkey);
            i++;
            verificacion[3] = 1;
        }
//Lee la tecla asociada al desplazamiento hacia la derecha
        else if ((strstr("RIGHT", movement)) != NULL) {
            configurar_tecla(&right, movementkey);
            i++;
            verificacion[4] = 1;
        }

	}

	fclose(pf);
//Verifica si hubo algún fallo al cargar la ip, el puerto o las teclas del jugador
    for( i = 0 ; i < 5 && (fallo == 0) ; i++){
        if(verificacion[i] == 0)
            fallo = 1;
    }

    if (fallo == 1){
        printf("Error. No se cargaron todos los datos requeridos.\nVerifique el archivo de configuración.\n");
        exit(1);
    }

    //std::vector<IActor*> actors;
    //std::vector<IActor*>::iterator actorsIter;

    Timer fps;

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(950, 600, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    if(TTF_Init() == -1) {
        exit(54);
    }

//Verifica los parámetros recibidos
    if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0))
    {
        printf("AYUDA\n");
        printf("Modo de uso:\n");
        printf("./cliente.exe <ip> <puerto>\n");
         exit(EXIT_SUCCESS);
    }
    if(argc < 3){
        printf("Cantidad inválida de parámetros\n");
        printf("-h para ayuda\n");
        exit(EXIT_FAILURE);
    }


    int sockfd = 0, n = 0;
    //char recvBuff[1024];
    struct sockaddr_in serv_addr;


    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    //int port =  atoi(argv[2]);
    //printf("Puerto %s",argv[2]);
    //printf("Puerto %d",port);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port );

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }
    i = 1;
    setsockopt( sockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&i, sizeof(i));



    Fleet f;
    Bullet b3;
    f.asignBullet(&b3);

    Barrier bar1(100,450,0);
    Barrier bar2(100,90,1);


    Ship s2;
    s2.position(  (GAME_W /2)  - 100 ,10);
	s2.setMode(2);
    Bullet b2;
    b2.setDownOrientation();
    s2.asignBullet(&b2);


    Ship s1;
	s1.setMode(1);
    s1.position( (GAME_W / 2)- 100 , GAME_H-60);
    Bullet b1;
    s1.asignBullet(&b1);

    Bonus bonus;
    SideBar sb;

    actors.push_back(&s1);
    actors.push_back(&s2);

    actors.push_back(&b1);
    actors.push_back(&b2);
    actors.push_back(&b3);
    actors.push_back(&f);

    actors.push_back(&bar1);
    actors.push_back(&bar2);
    actors.push_back(&bonus);
    actors.push_back(&sb);

    int loopN=0;
    Uint8 * keystate;
    bool done = false;
    while (!done)
    {
        //Start the frame timer
        fps.start();
        /*
        keystate = SDL_GetKeyState(NULL);

        if(keystate[SDLK_LEFT]) {
            s1.moveLeft();
        }
        if(keystate[SDLK_RIGHT]) {
            s1.moveRight();
            //printf("%s" ,bonus.toString().c_str());
            //s1.updateState("500,500\n");
            //b1.updateState("1|200,200\n");
        }

        if(keystate[SDLK_a]) {
            s2.moveLeft();
        }
        if(keystate[SDLK_d]) {
            s2.moveRight();
        }
        */

        std::string command = " ";

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;
                // check for keypresses
                case SDL_KEYDOWN:
                        // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                       done = true;
                    }
                    /*
                    if (event.key.keysym.sym == SDLK_w) {
                        //s2.fire();

                    }
                    */
                    if (event.key.keysym.sym == shoot) {
                        //s1.fire();
                        command = "1";
                    }

                    if (event.key.keysym.sym == left) {
                        //s1.moveLeft();
                        command = "2";
                    }

                    if (event.key.keysym.sym == right) {
                        //s1.moveRight();
                        command = "3";
                    }

                break;
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        if(command.compare(" ") != 0){
            //printf("Envio command!!\n");
            send(sockfd, command.c_str(), command.length(),0);
            command = " ";
        }


        int cantBytes=0;
        //char sendBuff[100];
    	cantBytes = recv(sockfd, recvBuff, strlen(recvBuff), 0);
        //recvBuff[cantBytes] = '\0';

        stringToGameState(std::string(recvBuff),actors);

		
		dibujar();
		/*
        // draw bitmap
		
        for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
            (*it)->blit();
        }

        memset(recvBuff, '0',sizeof(recvBuff));

        // DRAWING ENDS HERE


        SDL_Flip(screen);

        //Cap the frame rate
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
        }
	*/

    } // end main loop

    // free loaded bitmap
    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->free();
    }

    printf("Exited cleanly\n");
    return 0;
}

void dibujar(){

        // draw bitmap
		
        for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
            (*it)->blit();
        }

        memset(recvBuff, '0',sizeof(recvBuff));

        // DRAWING ENDS HERE


        SDL_Flip(screen);

        //Cap the frame rate
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
        }


}


std::string gameStateToString(std::vector<IActor*> actors){
    std::stringstream ss;

    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        //printf("%s" ,(*it)->toString().c_str());
        ss << (*it)->toString();

    }
    //printf("\n\n");
    return ss.str();
    //printf("%s ",ss.str().c_str());
    //std::cout << ss.str();
};


void stringToGameState(std::string sstate, std::vector<IActor*> actors) {

    std::istringstream f(sstate);
    std::string segment;

    //printf("State: %s ",sstate.c_str());
    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        //printf("%s" ,(*it)->toString().c_str());
        std::getline(f, segment);
        //printf("segment: %s \n", segment.c_str());
        (*it)->updateState(segment);
        //std::cout << "Tu vieja \n";
    }

    //std::getline(f, segment);
    //printf("segment: %s ",segment.c_str());

    //std::cout << ss.str();
};




int configuracion()
{
	screen = SDL_SetVideoMode(GAME_WC, 300, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    Timer fps;

	char line[40];
	char line2[10];
	fscanf( pf, "%s", line );
	fscanf( pf, "%s", line2 );
	printf("%s\n", line);
	printf("%s\n", line2);
	fclose(pf);
	Configmenu confme;
	FILE * pftemp;
	remove("conf/configuracion.txt");
	pftemp = fopen("conf/configuracion2.txt","wt");
    if( pftemp == NULL ){
        printf("Error en la apertura del archivo de configuracion\n");
        exit(1);
	}
	fprintf(pftemp, "%s\n", line);
	fprintf(pftemp, "%s\n", line2);

    bool done = false;
    char movement[3][8] = { "SHOOT" , "LEFT" , "RIGHT"};
    int i = 0;
    bool flag = false;
    while(!done)
    {
        fps.start();
        SDL_Event event;

        if ( i == 1 && flag == true ){
            fprintf( pftemp, "%s %s\n", movement[i-1], SDL_GetKeyName(event.key.keysym.sym));
            confme.SetOption3("mover a la izquierda");
            flag = false;
        }
        if ( i == 2 && flag == true ){
            fprintf( pftemp, "%s %s\n", movement[i-1], SDL_GetKeyName(event.key.keysym.sym));
            confme.SetOption3("mover a la derecha");
            flag = false;
        }
        if ( i == 3 && flag == true ){
            fprintf( pftemp, "%s %s\n", movement[i-1], SDL_GetKeyName(event.key.keysym.sym));
            confme.SetOption2("Presiones para salir");
            confme.SetOption3(" ");
            flag = false;
        }
        if ( i == 4 ) done = true;


        while (SDL_PollEvent(&event) && !done)
        {

            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                        // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                       done = true;
                    }
                    else{
                        i++;
                        if ( i == 1 || i == 2 || i == 3 ) {
                            flag = true;
                            printf("Valor de i: %d\n", i);
                        }
                    }
                    break;
                break;
            } // end switch
        } // end of message processing
		
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        confme.blit();

        //finally, update the screen :)
        SDL_Flip(screen);

        //Cap the frame rate
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
        }
    }
	
    fclose(pftemp);
    rename("conf/configuracion2.txt", "conf/configuracion.txt");
    confme.free();
}

void configurar_tecla(SDLKey *tecla,const char leer[30])
{
	int num;

	if(strstr(leer,"right") != NULL)
		num=0;

	if(strstr(leer,"left") != NULL)
		num=1;

	if(strstr(leer,"q")!=NULL)
		num=2;

	if(strstr(leer,"w")!=NULL)
		num=3;

	if(strstr(leer,"e")!=NULL)
		num=4;

	if(strstr(leer,"r")!=NULL)
		num=5;

	if(strstr(leer,"t")!=NULL)
		num=6;

	if(strstr(leer,"y")!=NULL)
		num=7;

	if(strstr(leer,"u")!=NULL)
		num=8;

	if(strstr(leer,"i")!=NULL)
		num=9;

	if(strstr(leer,"o")!=NULL)
		num=10;

	if(strstr(leer,"p")!=NULL)
		num=11;

	if(strstr(leer,"a")!=NULL)
		num=12;

	if(strstr(leer,"s")!=NULL)
		num=13;

	if(strstr(leer,"d")!=NULL)
		num=14;

	if(strstr(leer,"f")!=NULL)
		num=15;

	if(strstr(leer,"g")!=NULL)
		num=16;

	if(strstr(leer,"h")!=NULL)
		num=17;

	if(strstr(leer,"j")!=NULL)
		num=18;

	if(strstr(leer,"k")!=NULL)
		num=19;

	if(strstr(leer,"l")!=NULL)
		num=20;

	if(strstr(leer,"z")!=NULL)
		num=21;

	if(strstr(leer,"x")!=NULL)
		num=22;

	if(strstr(leer,"c")!=NULL)
		num=23;

	if(strstr(leer,"v")!=NULL)
		num=24;

	if(strstr(leer,"b")!=NULL)
		num=25;

	if(strstr(leer,"n")!=NULL)
		num=26;

	if(strstr(leer,"m")!=NULL)
		num=27;

	if(strstr(leer,"space")!=NULL)
		num=28;

	if(strstr(leer,"up") != NULL)
		num=30;

	switch(num)
	{
		case 0:
			*tecla = SDLK_RIGHT;
			break;

		case 1:
			*tecla = SDLK_LEFT;
			break;

		case 2:
			*tecla = SDLK_q;
			break;

		case 3:
			*tecla = SDLK_w;
			break;

		case 4:
			*tecla = SDLK_e;
			break;

		case 5:
			*tecla = SDLK_r;
			break;
		case 6:
			*tecla = SDLK_t;
			break;

		case 7:
			*tecla = SDLK_y;
			break;

		case 8:
			*tecla = SDLK_u;
			break;

		case 9:
			*tecla = SDLK_i;
			break;

		case 10:
			*tecla = SDLK_o;
			break;

		case 11:
			*tecla = SDLK_p;
			break;

		case 12:
			*tecla = SDLK_a;
			break;

		case 13:
			*tecla = SDLK_s;
			break;

		case 14:
			*tecla = SDLK_d;
			break;

		case 15:
			*tecla = SDLK_f;
			break;

		case 16:
			*tecla = SDLK_g;
			break;

		case 17:
			*tecla = SDLK_h;
			break;

		case 18:
			*tecla = SDLK_j;
			break;

		case 19:
			*tecla = SDLK_k;
			break;

		case 20:
			*tecla = SDLK_l;
			break;

		case 21:
			*tecla = SDLK_z;
			break;

		case 22:
			*tecla = SDLK_x;
			break;

		case 23:
			*tecla = SDLK_c;
			break;

		case 24:
			*tecla = SDLK_v;
			break;

		case 25:
			*tecla = SDLK_b;
			break;

		case 26:
			*tecla = SDLK_n;
			break;

		case 27:
			*tecla = SDLK_m;
			break;

		case 28:
			*tecla = SDLK_SPACE;
			break;

		case 30:
			*tecla = SDLK_UP;
			break;
		default:
			printf("\nTecla no reconocida, cambie el archivo de configuracion\n");
			exit(1);
			break;

	}
}
