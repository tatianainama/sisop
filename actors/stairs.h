#ifdef _STAIRS

#else
#define _STAIRS 1
#include "../iactor.h"
#include <SDL/SDL.h>
#include <stdlib.h>
#include <sstream>
#include <string>

extern SDL_Surface * screen;

class Stairs: public IActor {

public:
    static const int SHIPS_QTY = 10;
    int speed;
    int state;

    SDL_Rect rect[SHIPS_QTY];
    //int shipsf[SHIPS_QTY];
    SDL_Surface* bmp;

    Stairs(int, int, int);
    void say(void);

    void moveUp();
    void moveDown();
    void reset();
    void fire(int, int);
    void position(int , int );
    void blit();
    void update();
    void free();

    void setDownOrientation();
    void setUpOrientation();
    int getState();

    std::string toString();
    void updateState(std::string s);
};

#endif

