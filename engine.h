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

#include "actors/floor.h"
#include "actors/bonus.h"
#include "actors/mario.h"
#include "actors/stairs.h"
#include "actors/sidebar.h"
#include "actors/monkey.h"

#define MARIO_Y 40
#define WINNER 3



class Engine {

	public:

		Mario * s1;
		Mario * s2;
		Mario * pauline;
		Floor * bar1;
		Bonus * bonus;
		Stairs * stairs;
		SideBar * sb;
		Monkey * monkey;
		int paulineCont = 0;
		bool done;

		Engine();
		int run();
		int initSDL();
		void capturekeys();
		void update();
		void afterUpdate();

		void render();
		void free();

		void applyCommand(std::string,int);

		std::string gameStateToString();
		void stringToGameState(std::string);

};
