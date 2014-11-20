#include "local.h"

int main(int argc, char ** argv){
	
	Engine eng;
	Timer fps;
		
	eng.initSDL();

	while (!eng.done) {

        fps.start();

        eng.capturekeys();

        eng.update();	    		
        eng.afterUpdate();
    
        eng.render();
        
	    //Cap the frame rate
	    if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
	        SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
	    }

	} //end game loop

    eng.free();

    printf("Exited cleanly\n");
    return 0;
}

