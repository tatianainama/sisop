#include <SDL/SDL.h>
#include <stdlib.h>
#include "../iactor.h"
#include "../timer.h"
#include <time.h>

#include <sstream>
#include <string>

extern int gNum;
extern SDL_Surface * screen;

class Bonus : public IActor{

public:
    static const int SHIPS_QTY = 8;
    SDL_Rect rect[SHIPS_QTY];
    int shipsf[SHIPS_QTY];    
    int speed;
    int speedY;
    int aliveMarios;
    Timer t;
    int dir;
    int moveQty;
    SDL_Surface* bmp;

    int state;
    int isServer;
    bool climbing[SHIPS_QTY];
    int speedf[SHIPS_QTY];


    Bonus(int,int);

    void say(void);
    void moveLeft();
    void moveRight();
    void moveDown(int);
    void move(int);

    void position(int , int );
    void blit();
    void update();
    void reset(int);
    void free();

    int getX();
    int getY();

    std::string toString();
    void updateState(std::string);

};

