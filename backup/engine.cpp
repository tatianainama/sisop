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
#include "actors/bonus.h"
#include "sidebar.h"
#include "menu.h"
#include "stairs.h"

#include<vector>

const int FRAMES_PER_SECOND = 50;

SDL_Surface * screen;


std::vector<IActor*> actors;
Timer fps;


bool check_collision( SDL_Rect, SDL_Rect);

/*
mover a:
engine.init()
engine.input
engine.render
engine.update o 'tick'/beat ? vs blit/render
engine.applyCommand
engine.statetoString serializeState
engine.stringToState unserializeState
*/

int main ( int argc, char** argv ){

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    // create a new window
    screen = SDL_SetVideoMode(900, 600, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }


    Fleet f;
    Bullet b3;
    f.asignBullet(&b3);



    Barrier bar1(000,98,1);
   	/* Barrier bar2(000,200,1);
    Barrier bar3(000,300,1);
	Barrier bar4(000,400,0);
	Barrier bar5(000,500,0);
	Barrier bar6(000,599,0);*/


    Ship s2;
    s2.position(  (GAME_W /2)  + 100 ,GAME_H-30);
	//s2.setMode(2);
   	Bullet b2;
    b2.setDownOrientation();
    s2.asignBullet(&b2);


    Ship s1;
	//s1.setMode(1);
    s1.position( (GAME_W / 2)- 100 , GAME_H-30);
    Bullet b1;
    s1.asignBullet(&b1);


    SideBar sb;



    actors.push_back(&b1);
    actors.push_back(&b2);
   // actors.push_back(&b3);
   // actors.push_back(&f);

    actors.push_back(&bar1);


    Bonus bonus;
    actors.push_back(&bonus);
    actors.push_back(&sb);

    Stairs stairs(160,98,1);
    actors.push_back(&stairs);   

    actors.push_back(&s1);
    actors.push_back(&s2);

    Uint8 * keystate;
    bool done = false;

    while (!done)
    {
        //Start the frame timer
        fps.start();

        keystate = SDL_GetKeyState(NULL);
        if(keystate[SDLK_LEFT]) {
        	//if(!s1.climbing){
            	s1.moveLeft();
        	//}
        }
        if(keystate[SDLK_RIGHT]) {
            s1.moveRight();
        }

        if(keystate[SDLK_UP]) {
        	int collided = 0;
        	if(s1.onGround){
	        	for (int i=0; i<Stairs::SHIPS_QTY; i++) {
	                if (check_collision(s1.rect,stairs.rect[i])) {
	                	s1.climbing = true;
	                	s1.moveUp();
	                	collided = 1;
	                	//std::cout << "Climbing en true??" << s1.climbing << "\n";
	                }
	            }
				if(!collided){
					std::cout << "ELSEClimbing en true??" << s1.climbing << "\n";

	                s1.climbing= false;
	                s1.onGround = false;

	        		/*std::cout << "stairs width " << stairs.rect[1].w << "\n";
	        		std::cout << "stairs height " << stairs.rect[1].h << "\n";*/
				}
			}

        }

        if(keystate[SDLK_DOWN]) {
        	for (int i=0; i<Stairs::SHIPS_QTY; i++) {
                if (check_collision(s1.rect,stairs.rect[i])) {
                	SDL_Rect * r;
                	r = bar1.getNextBaseFloor(stairs.rect[i].y+stairs.rect[i].h);
                	std::cout << "Recta a chequear <<<<<<< " << r->y << " \n";
                	if(s1.rect.y+s1.rect.h >= r->y){
                		std::cout << "Entra al if " << "  \n"; 
                		s1.onGround = false;
                		s1.climbing = false;
                	} else{
                	s1.climbing = true;
                	//S1.climbingDown = true;
                	s1.moveDown();

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
            s2.moveLeft();
        }
        if(keystate[SDLK_d]) {
            s2.moveRight();
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
                        s2.jump();
                    }
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        s1.jump();
                    }
                break;
            } // end switch
        }

	    // clear screen
	    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));



		
	    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
	        (*it)->blit();
	    }

	    if(!s1.climbing  && !s1.onGround){

	    	for (int i=0; i<Barrier::SHIPS_QTY; i++) {
                if (check_collision(s1.rect,bar1.rect[i])) {
                	//s1.climbing = true;
                	//S1.climbingDown = true;
                	//std::cout << "Climbing en true??" << s1.climbing << "\n";
                	//s1.moveDown();
	               /* std::cout << "entra en collision con bar" << i << " \n";
			    	std::cout << "climb" << s1.climbing << "\n";
			    	std::cout << "onGround" << s1.onGround << "\n";
			    	std::cout << "end col" << "\n";*/
			    	s1.rect.y = bar1.rect[i].y-28;
		        	s1.speedY = 0.0;
		        	s1.onGround = true;
	        	}
            }
	    	    
		}

		if(s1.climbing){
			int collided = 0;
        	for (int i=0; i<Stairs::SHIPS_QTY; i++) {
                if (check_collision(s1.rect,stairs.rect[i])) {
                	//s1.climbing = true;
                	//s1.moveUp();
                	collided = 1;
                	//std::cout << "Climbing en true??" << s1.climbing << "\n";
                }
            }
			if(!collided){
				//std::cout << "ELSEClimbing en true??" << s1.climbing << "\n";
                s1.climbing= false;
                s1.onGround = false;
        		//std::cout << "stairs width " << stairs.rect[1].w << "\n";
        		//std::cout << "stairs height " << stairs.rect[1].h << "\n";
			}
		}




    	for (int i=0; i<Stairs::SHIPS_QTY; i++) {
            if (check_collision(bonus.rect,stairs.rect[i])) {
            	SDL_Rect * r;
            	r = bar1.getNextBaseFloor(stairs.rect[i].y+stairs.rect[i].h);
            	//std::cout << "Recta a chequear <<<<<<< " << r->y << " \n";
            	if(bonus.rect.y+bonus.rect.h > r->y){
            		//std::cout << "Entra al if " << "  \n"; 
            		//s1.onGround = false;
            		bonus.climbing = false;
            	} else{
            	bonus.climbing = true;
            	//S1.climbingDown = true;
            	//s1.moveDown();

				}
            	//std::cout << "Climbing en true??" << s1.climbing << "\n";
   
            }else{
            	//std::cout << "Entra al else Climbing en true??" << s1.climbing << "\n";
            	//s1.climbing= false;
            	//s1.onGround = false;
            }
        }


	        
	    SDL_Flip(screen);

	    //Cap the frame rate
	    if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
	        SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
	    }

	}//end game loop




    for(std::vector<IActor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
        (*it)->free();
    }

    printf("Exited cleanly\n");
    return 0;
}


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
