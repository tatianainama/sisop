#include <SDL/SDL.h>
#include <stdlib.h>

#include "../iactor.h"
#include <sstream>
#include <string>

#define _MSHIP1 "img/ship1.bmp"
#define _MSHIP2 "img/ship2.bmp"

extern int gNum;
extern SDL_Surface * screen;

class Monkey : public IActor {

public:
    int speed;
    SDL_Rect rect;
    SDL_Surface* bmp;

    bool onGround;
    bool climbing;
    int speedY;
    int grav;

    Monkey(void);
    void say(void);
	
	void setMode(int);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void position(int , int );
    void blit();
    void update();
    void free();

    int getX();
    int getY();
    void jump();

    std::string toString();
    void updateState(std::string);

};
