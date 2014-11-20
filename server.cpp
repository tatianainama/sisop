#include "server.h"
#include "network.cpp"
int main(int argc, char ** argv){

	Timer fps;
	Engine eng;
	std::string remoteCommand;
	std::istringstream temp;
	int command;
	//eng.initSDL();

	Network n;
	int sockfd = n.nsocket();

	std::cout << "server";

	n.nlisten(sockfd,4545);
	fflush(stdout);

	int confd = n.naccept(sockfd);
  	std::cout << "Accepted\n";


	while (!eng.done) {
        //Start the frame timer
        fps.start();

        //eng.capturekeys();

        eng.update();
	    		
        eng.afterUpdate();
	    
        //eng.render();
  	    
  	    //std::cout << eng.gameStateToString();
  	    //std::cout << "tamano" << eng.gameStateToString().length();
  	    
  	    n.nsend(confd,eng.gameStateToString());
  	    
  	    //std::cout << "ya envie estado----------------\n";
	    
	    remoteCommand = n.nreceive(confd);
	    eng.applyCommand(remoteCommand);
	    remoteCommand = "";
	    //Cap the frame rate
	    if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
	        SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
	    }

	} //end game loop

    eng.free();

    printf("Exited cleanly\n");
    return 0;
}