#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#include "../iactor.h"
#include <sstream>
#include <string>

#define _MARIO1 "img/mario.png"
#define _MARIO2 "img/mario2.png"
#define _PAULINE "img/pauline_vector.png"

#define MARIO_FRAMES 6

extern int gNum;
extern SDL_Surface * screen;

class Mario : public IActor {

public:
    int speed;
    int cantPau;
    SDL_Rect source ,rect;
    SDL_Surface* img;

    bool onGround;
    bool climbing;
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    int speedY;
    int grav;

    Mario(void);
    void say(void);
		SDL_Surface* loadImage(const char*);
		void setMode(int);
    void setImage(const char *);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
		
		void newPauline();
		int getPaulines();
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
