#ifdef _BARRIER

#else
#define _BARRIER 1
#include "../iactor.h"
#include <SDL/SDL.h>
#include <stdlib.h>
#include <sstream>
#include <string>

 extern SDL_Surface * screen;

class Floor: public IActor {

public:
    static const int offsetBetweenBarriers = 400;
    static const int blockOfBarriers = 1;

    int offset;
    static const int SHIPS_QTY = 7;
    int speed;
    int state;
    int dir;
    int moveQty;
    int orientation;
    SDL_Rect rect[SHIPS_QTY];
    //int shipsf[SHIPS_QTY];
    SDL_Surface* bmp;

    Floor(int, int, int);
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

    SDL_Rect * getNextBaseFloor(int);

};

#endif

