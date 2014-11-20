#include "client.h"
#include "network.cpp"


void captureKeys(int,Network);
bool done = false;
int main(int argc, char ** argv){
	Engine eng;
	std::string remoteGameState;
	Timer fps;
		
	eng.initSDL();


	Network n;
	int sockfd = n.nsocket();
	n.nconnect(sockfd,"127.0.0.1",4545);


	while (!done) {

        fps.start();

        /*eng.capturekeys();
        eng.update();	    		
        eng.afterUpdate();
		*/
        
        remoteGameState = n.nreceive(sockfd);
        eng.stringToGameState(remoteGameState);
	    

        eng.render();
        
        captureKeys(sockfd,n);
	    //Cap the frame rate
	    if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
	        SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
	    }

	} //end game loop

    eng.free();

    printf("Exited cleanly\n");
    return 0;
}

		
	/*
	* Mock de una respuesta del servidor
	*
    std::stringstream ss;
    ss << "0\n";
    ss << "0\n";
    ss << "0\n";
    ss << "520,560\n";
    ss << "500,560\n";
    ss << "1,604,108|1,640,108|1,400,108|0,400,108|0,400,108|0,400,108|0,400,108|0,400,108\n";
    ss << "4,0,4,0\n";
	ss << "400,560\n";

    eng.stringToGameState(ss.str());
	*/

void captureKeys(int sockfd, Network n){
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
			        std::cout << "Envio comando 1\n";
			        command = "1";					
			    }
			    if(event.key.keysym.sym == SDLK_RIGHT) {
			        //s1->moveRight();
			        std::cout << "Envio comando 2\n";
			        command = "2";
			    }
			    if(event.key.keysym.sym == SDLK_UP) {
			        //s1->moveRight();
			        std::cout << "Envio comando 3\n";
			        command = "3";
			    }
			    if(event.key.keysym.sym == SDLK_DOWN) {
			        //s1->moveRight();
			        std::cout << "Envio comando 4\n";
			        command = "4";
			    }

                if (event.key.keysym.sym == SDLK_SPACE) {
                    //s1->jump();
			        std::cout << "Envio comando 5\n";                    
                    command = "5";
                }	    

			break;

			case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_LEFT) {
			        //s1->moveLeft();
			        std::cout << "Envio comando 8\n";
			        command = "8";					
			    }
			    if(event.key.keysym.sym == SDLK_RIGHT) {
			        //s1->moveRight();
			        std::cout << "Envio comando 9\n";
			        command = "9";
			    }
			    if(event.key.keysym.sym == SDLK_UP) {
			        //s1->moveRight();
			        std::cout << "Envio comando 7\n";
			        command = "7";
			    }
			    if(event.key.keysym.sym == SDLK_DOWN) {
			        //s1->moveRight();
			        std::cout << "Envio comando 6\n";
			        command = "6";
			    }			    
			break;

		}// end switch
	}
			       
	n.nsend(sockfd,command);

};