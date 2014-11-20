#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


#include <sys/ioctl.h>


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
std::string gameStateToString(std::vector<IActor*> );
void stringToGameState(std::string, std::vector<IActor*>);

bool check_collision(SDL_Rect, SDL_Rect);


int main ( int argc, char** argv )
{

    std::vector<IActor*> actors;
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

    /*
    //The font that's going to be used
    TTF_Font *font = NULL;
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 48 );
    SDL_Surface *message = NULL;
    //If there was an error in loading the font
    if( font == NULL )
    {
        exit(23);
        printf("asd");
    }
    SDL_Color textColor = { 255, 255, 255 };
    message = TTF_RenderText_Solid( font, "The quick brown fox jumps over the lazy dog", textColor );
    SDL_Rect msgRect;
    msgRect.x=10;
    msgRect.y=10;
     //apply_surface( 0, 150, message, screen );
    */


    int listenfd = 0, connfd = 0, connfd2=0;
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    int port = 4000;//atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    //connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    int m = 1;
    //setsockopt( connfd, IPPROTO_TCP, TCP_NODELAY, (void *)&m, sizeof(m));
   // ConfigJuego conf[40];
    //conf.connfd = connfd;
    //int q=0;
    printf("Starting to accept con \n");
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    connfd2 = accept(listenfd, (struct sockaddr*)NULL, NULL);


    setsockopt( connfd, IPPROTO_TCP, TCP_NODELAY, (void *)&m, sizeof(m));
    setsockopt( connfd2, IPPROTO_TCP, TCP_NODELAY, (void *)&m, sizeof(m));





    long on = 1L;
    if (ioctl(connfd, (int)FIONBIO, (char *)&on))
    {
        printf("ioctl FIONBIO call failed\n");
    }
    if (ioctl(connfd2, (int)FIONBIO, (char *)&on))
    {
        printf("ioctl FIONBIO call failed\n");
    }
    printf("Client Connected \n");
    //connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);



    Fleet f;
    Bullet b3;
    f.asignBullet(&b3);
    f.isServer=1;
    //b3.speed = 30;

    Barrier bar1(100,450,0);
    Barrier bar2(100,90,1);


    Ship s2;
	s2.setMode(2);
    s2.position(  (GAME_W /2)  - 100 ,10);
    Bullet b2;
    b2.setDownOrientation();
    s2.asignBullet(&b2);


    Ship s1;
	s1.setMode(1);
    s1.position( (GAME_W / 2)- 100 , GAME_H-60);
    Bullet b1;
    s1.asignBullet(&b1);
    b2.speed = 30;

    b1.speed = 30;
    //s1.speed = 15;
    //s2.speed = 15;

    Bonus bonus;
    bonus.isServer=1;
    SideBar sb;
   // sb.setName1("Tu vieja");

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

/*
    std::stringstream streamst;
    //std::string streamst;
    streamst << "300,540\n";
    streamst <<"300,10\n";
    streamst << "0|900,900\n";
    streamst << "0|900,900\n";
    streamst << "0|900,900\n";
    streamst << "10,220|1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1\n";
    streamst << "1,1,1,1,0,1,1,1,1,1,0,1,1,0,0,1,0,1\n";
    streamst << "0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1\n";
    streamst << "0|0,400\n";
    streamst << "0";

    //printf("STATE:::: %s",streamst.str().c_str());
    stringToGameState(streamst.str(), actors);
*/
    Uint8 * keystate;
    bool done = false;


    int cantBytes;
    char recvBuff[40];

    int cantBytes2;
    char recvBuff2[40];

    memset(recvBuff, '0',sizeof(recvBuff));
    memset(recvBuff2, '0',sizeof(recvBuff2));
    while (!done)
    {
        //Start the frame timer
        fps.start();



        //printf("Me fijo si hay comando recibido....\n");
    	cantBytes = recv(connfd, recvBuff, strlen(recvBuff), 0);
    	cantBytes2 = recv(connfd2, recvBuff2, strlen(recvBuff2), 0);

        if(cantBytes > 0){
            recvBuff[cantBytes] = '\0';
        }

        if(cantBytes2 > 0){
            recvBuff2[cantBytes2] = '\0';
        }

        if (recvBuff[0] - '0' == 1) {
            //printf("Recibi comando disparo!!!\n");
            //exit(0);
            s1.fire();
        } else if (recvBuff[0] - '0' == 2) {

            s1.moveLeft();

        } else if (recvBuff[0] - '0' == 3) {
            s1.moveRight();

        } else {
            //printf("No command\n");
            //printf("recvBuff: %s\n",recvBuff);
        }


        if (recvBuff2[0] - '0' == 1) {
            //printf("Recibi comando disparo!!!\n");
            //exit(0);
            s2.fire();
        } else if (recvBuff2[0] - '0' == 2) {

            s2.moveLeft();

        } else if (recvBuff2[0] - '0' == 3) {
            s2.moveRight();

        } else {
            //printf("No command\n");
            //printf("recvBuff: %s\n",recvBuff);
        }



        memset(recvBuff, '0',sizeof(recvBuff));
        memset(recvBuff2, '0',sizeof(recvBuff2));
        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        if(b2.getState() ==1) {

            if (check_collision(s1.rect,b2.rect)) {
                b2.reset();
                s1.rect.x=0;
		sb.addToLife1(-1);
		sb.addToScore2(400);
            }
            for (int i=0; i<Fleet::SHIPS_QTY; i++) {
                if (f.shipsf[i] == 1 && check_collision(b2.rect,f.rect[i])) {
                        f.shipsf[i] = 0;
                        f.aliveShips--;
                        b2.reset();
			sb.addToScore2(100);
                }
            }
            for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (bar1.shipsf[i] == 1 && check_collision(b2.rect,bar1.rect[i])) {
                        bar1.shipsf[i] = 0;
                        b2.reset();
                }
            }
            for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (bar2.shipsf[i] == 1 && check_collision(b2.rect,bar2.rect[i])) {
                        bar2.shipsf[i] = 0;
                        b2.reset();
                }
            }

            if (check_collision(bonus.rect,b2.rect)) {
                b2.reset();
                bonus.reset();
            }
        }


        if(b1.getState() == 1){
            if (check_collision(s2.rect,b1.rect)) {
                b1.reset();
                s2.rect.x=0;
		sb.addToLife2(-1);
		sb.addToScore1(400);
            }
            for (int i=0; i<Fleet::SHIPS_QTY; i++) {
                if (f.shipsf[i] == 1 && check_collision(b1.rect,f.rect[i])) {
                        f.shipsf[i] = 0;
                        f.aliveShips--;
                        b1.reset();
			sb.addToScore1(100);
                }
            }
            for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (bar1.shipsf[i] == 1 && check_collision(b1.rect,bar1.rect[i])) {
                        bar1.shipsf[i] = 0;
                        b1.reset();
                }
            }
            for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (bar2.shipsf[i] == 1 && check_collision(b1.rect,bar2.rect[i])) {
                        bar2.shipsf[i] = 0;
                        b1.reset();
                }
            }

            if (check_collision(bonus.rect,b1.rect)) {
                b1.reset();
                bonus.reset();
            }

        }

        if(b3.getState() == 1){
            if (check_collision(s1.rect,b3.rect)) {
                b3.reset();
                s1.rect.x=0;
		sb.addToLife1(-1);
            }
            if (check_collision(s2.rect,b3.rect)) {
                b3.reset();
                s2.rect.x=0;
		sb.addToLife2(-1);
            }
            for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (bar1.shipsf[i] == 1 && check_collision(b3.rect,bar1.rect[i])) {
                        bar1.shipsf[i] = 0;
                        b3.reset();
                }
            }
            for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (bar2.shipsf[i] == 1 && check_collision(b3.rect,bar2.rect[i])) {
                        bar2.shipsf[i] = 0;
                        b3.reset();
                }
            }

        }


        // draw bitmap
        for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
            (*it)->blit();
        }

        //SDL_BlitSurface( message, 0, screen, &msgRect);
        // DRAWING ENDS HERE

        //finally, update the screen :)
        //for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
          //  printf("%s" ,(*it)->toString().c_str());
            //printf("%d", 1);
        //}
       // gameStateToString(actors);


       // SDL_Flip(screen);

        std::string gameSt =  gameStateToString(actors);

        send(connfd, gameSt.c_str(), gameSt.length(),0);
        send(connfd2, gameSt.c_str(), gameSt.length(),0);
        //printf("gameSt:\n %s ", gameSt.c_str());
        //printf("\n\n");

        //Cap the frame rate
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
        }

    } // end main loop

    // free loaded bitmap
    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->free();
    }

    printf("Exited cleanly\n");
    return 0;
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


void stringToGameState(std::string sstate, std::vector<IActor*> actors){

    std::stringstream f(sstate);
    std::string segment;


    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        //printf("%s" ,(*it)->toString().c_str());
        std::getline(f, segment);
        printf("segment: %s \n", segment.c_str());
        (*it)->updateState(segment);
    }


};




bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    //Here we have the actual function that checks for a collision.

    //First thing the function does is take in the SDL_Rects and calculate their sides.
    //If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
};

