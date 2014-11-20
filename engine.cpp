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
#include "engine.h"

#include<vector>



SDL_Surface * screen;


std::vector<IActor*> actors;
Timer fps;


bool check_collision( SDL_Rect, SDL_Rect);


Engine::Engine(){

    done = false;

	  std::cout << "Engine Constructor" << " \n";
	  initSDL();
    bar1 = new Floor(0,50,1);
    
    s2 = new Mario();
    s2->position(  (GAME_W /2)  + 100 ,GAME_H-MARIO_Y);
    s2->setMode(2);
    //s2.setMode(2);

    s1 = new Mario();
    
    s1->position( (GAME_W / 2)- 100 , GAME_H-MARIO_Y);
    //s1.setMode(1);
    

    pauline = new Mario();
    pauline->position( GAME_W / 2 +10, 20);
    pauline->setImage("img/pauline.bmp");

    bonus = new Bonus(GAME_W /2,112);
    
    sb = new SideBar();
    
    stairs = new Stairs(120,49,1);

    monkey = new Monkey();
    monkey->position(GAME_W / 2, 80);

    actors.push_back(bar1);

    actors.push_back(monkey);

    actors.push_back(stairs);
    actors.push_back(s1);
    actors.push_back(s2);
    actors.push_back(bonus);
    actors.push_back(sb);
    actors.push_back(pauline);
};

/*
int main( int argc, char** argv){
	Engine e;
	std::cout << "Engine Run" << " \n";
    e.init();
	e.run(); 

};
*/

int Engine::initSDL(){

    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;

    }
		printf( "INIT OK\n" );

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    // create a new window
    screen = SDL_SetVideoMode(900, 600, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
};



void Engine::update(){
    int i,collided = 0;

    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
            (*it)->update();
    }


    if(this->s1->onGround && this->s1->movingUp){
        for (i=0; i<Stairs::SHIPS_QTY; i++) {
            if (check_collision(this->s1->rect,this->stairs->rect[i])) {
                this->s1->climbing = true;
                this->s1->moveUp();
                collided = 1;
                //std::cout << "Climbing en true??" << s1.climbing << "\n";
            }
        }
        if(!collided){
            //std::cout << "ELSEClimbing en true??" << s1.climbing << "\n";
            this->s1->climbing= false;
            //s1->onGround = false;

            /*std::cout << "stairs width " << stairs.rect[1].w << "\n";
            std::cout << "stairs height " << stairs.rect[1].h << "\n";*/
        }
    }


    if(this->s1->movingDown){
        for (i=0; i<Stairs::SHIPS_QTY; i++) {
            if (check_collision(this->s1->rect,this->stairs->rect[i])) {
                //std::cout << "Colision con stair <<<<<<< " <<  " \n";
                SDL_Rect * r;
                r = this->bar1->getNextBaseFloor(stairs->rect[i].y+stairs->rect[i].h);
                if(r != NULL){
                //std::cout << "Recta a chequear <<<<<<< " << r->y << " \n";
                    if(this->s1->rect.y+this->s1->rect.h >= r->y){
                        //std::cout << "Entra al if " << "  \n"; 
                        this->s1->onGround = false;
                        this->s1->climbing = false;
                    } else{
                        this->s1->climbing = true;
                    //S1.climbingDown = true;
                        this->s1->moveDown();
                    }
                }
                //std::cout << "Climbing en true??" << s1.climbing << "\n";

            }else{
                //std::cout << "Entra al else Climbing en true??" << s1.climbing << "\n";
                //s1.climbing= false;
                //s1.onGround = false;
            }
        }
    }








};



int Engine::run(){

    while (!done) {
        //Start the frame timer
        fps.start();

        this->capturekeys();

        this->update();
	    		
        this->afterUpdate();
	    
        this->render();
  	    
	    //Cap the frame rate
	    if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
	        SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
	    }

	} //end game loop

    this->free();

    printf("Exited cleanly\n");
    return 0;
};


void Engine::applyCommand(std::string command){
    if(command == ""){
        return;
    }
int com;
std::istringstream ss(command);
int collided,i;
ss >> com;
    switch(com){

        case 1:
            this->s1->movingRight = false;
            this->s1->movingLeft = true;
        break;

        case 2:
            this->s1->movingLeft = false;
            this->s1->movingRight = true;
        break;

        case 3:
            /*this->s1->movingLeft = false;
            this->s1->movingRight = true;*/
            this->s1->movingDown = false;
            this->s1->movingUp = true;
        break;
    
        case 4:
            this->s1->movingUp = false;        
            this->s1->movingDown = true;

        break;


        case 5:
            this->s1->jump();
        break; 

        case 7:
            this->s1->movingUp = false;
        break; 

        case 6:
            this->s1->movingDown = false;
        break; 

        case 8:
            this->s1->movingLeft = false;
        break; 

        case 9:
            this->s1->movingRight = false;
        break; 

    }
};

void Engine::capturekeys(){


std::string command;
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

                if (event.key.keysym.sym == SDLK_w) {
                    //s2->jump();
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    //s1->jump();
                }

                if(event.key.keysym.sym == SDLK_LEFT) {
                    //s1->moveLeft();
                    //std::cout << "Envio comando 1\n";
                    command = "1";                  
                }
                if(event.key.keysym.sym == SDLK_RIGHT) {
                    //s1->moveRight();
                    //std::cout << "Envio comando 2\n";
                    command = "2";
                }
                if(event.key.keysym.sym == SDLK_UP) {
                    //s1->moveRight();
                    //std::cout << "Envio comando 3\n";
                    command = "3";
                }
                if(event.key.keysym.sym == SDLK_DOWN) {
                    //s1->moveRight();
                    //std::cout << "Envio comando 4\n";
                    command = "4";
                }

                if (event.key.keysym.sym == SDLK_SPACE) {
                    //s1->jump();
                    //std::cout << "Envio comando 5\n";                    
                    command = "5";
                }       

            break;

            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_LEFT) {
                    //s1->moveLeft();
                    //std::cout << "Envio comando 8\n";
                    command = "8";                  
                }
                if(event.key.keysym.sym == SDLK_RIGHT) {
                    //s1->moveRight();
                    //std::cout << "Envio comando 9\n";
                    command = "9";
                }
                if(event.key.keysym.sym == SDLK_UP) {
                    //s1->moveRight();
                    //std::cout << "Envio comando 7\n";
                    command = "7";
                }
                if(event.key.keysym.sym == SDLK_DOWN) {
                    //s1->moveRight();
                    //std::cout << "Envio comando 6\n";
                    command = "6";
                }               
            break;

        }// end switch
    }
    this->applyCommand(command);


    /*Uint8 * keystate;
    keystate = SDL_GetKeyState(NULL);
    if(keystate[SDLK_LEFT]) {
        //if(!s1.climbing){
            s1->moveLeft();
        //}
    }
    if(keystate[SDLK_RIGHT]) {
        s1->moveRight();
    }

    if(keystate[SDLK_UP]) {
        int collided = 0;
        if(s1->onGround){
            for (int i=0; i<Stairs::SHIPS_QTY; i++) {
                if (check_collision(s1->rect,stairs->rect[i])) {
                    s1->climbing = true;
                    s1->moveUp();
                    collided = 1;
                    //std::cout << "Climbing en true??" << s1.climbing << "\n";
                }
            }
            if(!collided){
                //std::cout << "ELSEClimbing en true??" << s1.climbing << "\n";
                s1->climbing= false;
                //s1.onGround = false;

            }
        }

    }

    if(keystate[SDLK_DOWN]) {
        for (int i=0; i<Stairs::SHIPS_QTY; i++) {
            if (check_collision(s1->rect,stairs->rect[i])) {
                //std::cout << "Colision con stair <<<<<<< " <<  " \n";
                SDL_Rect * r;
                r = bar1->getNextBaseFloor(stairs->rect[i].y+stairs->rect[i].h);
                if(r != NULL){
                //std::cout << "Recta a chequear <<<<<<< " << r->y << " \n";
                if(s1->rect.y+s1->rect.h >= r->y){
                    //std::cout << "Entra al if " << "  \n"; 
                    s1->onGround = false;
                    s1->climbing = false;
                } else{
                s1->climbing = true;
                //S1.climbingDown = true;
                s1->moveDown();
                }
                }
                //std::cout << "Climbing en true??" << s1.climbing << "\n";
   
            }else{
                //std::cout << "Entra al else Climbing en true??" << s1.climbing << "\n";
                //s1.climbing= false;
                //s1.onGround = false;
            }
        }               
    }

    if(keystate[SDLK_a]) {
        s2->moveLeft();
    }
    if(keystate[SDLK_d]) {
        s2->moveRight();
    }

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

                if (event.key.keysym.sym == SDLK_w) {
                    s2->jump();
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    s1->jump();
                }
            break;
        } // end switch
    }
*/

};


void Engine::afterUpdate(){
    if(!s1->climbing  && !s1->onGround){
        for (int i=0; i<Floor::SHIPS_QTY; i++) {
            if (check_collision(s1->rect,bar1->rect[i])) {
                //s1.climbing = true;
                //S1.climbingDown = true;
                //std::cout << "Climbing en true??" << s1.climbing << "\n";
                //s1.moveDown();
               /* std::cout << "entra en collision con bar" << i << " \n";
                std::cout << "climb" << s1.climbing << "\n";
                std::cout << "onGround" << s1.onGround << "\n";
                std::cout << "end col" << "\n";*/
                s1->rect.y = bar1->rect[i].y-s1->rect.h;
                s1->speedY = 0.0;
                s1->onGround = true;
            }
        }
            
    }

    if(s1->climbing){
        int collided = 0;
        for (int i=0; i<Stairs::SHIPS_QTY; i++) {
            if (check_collision(s1->rect,stairs->rect[i])) {
                //s1.climbing = true;
                //s1.moveUp();
                collided = 1;
                break;
                //std::cout << "Climbing en true??" << s1.climbing << "\n";
            }
        }
        if(!collided){
            //std::cout << "ELSEClimbing en true??" << s1.climbing << "\n";
            s1->climbing= false;
            s1->onGround = false;
            //std::cout << "stairs width " << stairs.rect[1].w << "\n";
            //std::cout << "stairs height " << stairs.rect[1].h << "\n";
        }
    }


    for (int j=0; j<Bonus::SHIPS_QTY; j++) {        
        if(bonus->shipsf[j] == 1){
            for (int i=0; i<Stairs::SHIPS_QTY; i++) {

                if (check_collision(bonus->rect[j],stairs->rect[i])) {
                    //std::cout << "chequeo contra escaleras \n";
                    SDL_Rect * r;
                    r = bar1->getNextBaseFloor(stairs->rect[i].y+stairs->rect[i].h);
                    //std::cout << "Recta a chequear <<<<<<< " << r->y << " \n";
                    if(bonus->rect[j].y+bonus->rect[j].h > r->y){
                        //std::cout << "Entra al if " << "  \n"; 
                        //s1.onGround = false;
                        bonus->climbing[j] = false;
                    } else{
                    bonus->climbing[j] = true;
                    //S1.climbingDown = true;
                    //s1.moveDown();

                    }
                    break;
                    //std::cout << "Climbing en true??" << s1.climbing << "\n";
       
                }else{
                    //std::cout << "Entra al else Climbing en true??" << s1.climbing << "\n";
                    //s1.climbing= false;
                    //s1.onGround = false;
                }
            }

             if (check_collision(bonus->rect[j],s1->rect)) {
                s1->position(GAME_W / 2- 100 , GAME_H-MARIO_Y);
             }
        }
    }
};


std::string Engine::gameStateToString(){
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


void Engine::stringToGameState(std::string sstate){

    std::stringstream f(sstate);
    std::string segment;

    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        //printf("%s" ,(*it)->toString().c_str());
        std::getline(f, segment);

        (*it)->updateState(segment);
    }
};



void Engine::render(){

    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->blit();
    }
    SDL_Flip(screen);    
};


void Engine::free(){
    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->free();
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
