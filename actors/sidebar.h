
#include <SDL/SDL.h>
#include <stdlib.h>
#include "SDL/SDL_ttf.h"
#include "../iactor.h"

#include <sstream>
#include <string>

#define _FONT "font/prstartk.ttf"
#define _FONT_SIZESB 10
#define _FONT_COLOR1 {0,255,0,0}
#define _FONT_COLOR2 {0,0,255,0}

#define _SHIP1 "img/shipLife1.bmp"
#define _SHIP2 "img/shipLife2.bmp"

#define _SEPARATIONSB 50

extern SDL_Surface * screen;

class SideBar : public IActor {

public:

	SDL_Color fontColor1;
	SDL_Color fontColor2;
    SDL_Rect rectSideBar;
	SDL_Surface*text_name1;
	SDL_Surface*text_name2;
	SDL_Surface*text_score1;
	SDL_Surface*text_score2;
	SDL_Surface*text_life1;
	SDL_Surface*text_life2;
	SDL_Surface*sidebar;

    SDL_Rect tempMario	;
    SDL_Surface* ship1;
    SDL_Surface* ship2;

	SDL_Rect rectName1;
	SDL_Rect rectName2;
	SDL_Rect rectScore1;
	SDL_Rect rectScore2;
	SDL_Rect rectLife1;
	SDL_Rect rectLife2;

	TTF_Font* font;

    SideBar(void);
	char Name1[10];
	char Name2[10];
	int Score1;
	int Score2;
	int Life1;
	int Life2;

	void setName1(const char[60]);
	void setName2(const char[60]);
	void setScore1(int);
	void setScore2(int);
	void setLife1(int);
	void setLife2(int);

	char* getName1();
	char* getName2();
	int getLife1();
	int getLife2();
	int getScore1();
	int getScore2();

	void addToScore1(int);
	void addToScore2(int);
	void addToLife1(int);
	void addToLife2(int);

    void blit();
    void free();

    void update();



    //Revisar
	void position(int , int );
    int getX();
    int getY();

    std::string toString();
    void updateState(std::string);
};
