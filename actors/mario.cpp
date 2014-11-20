#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <stdio.h>
#include "../constants.h"
#include "mario.h"
#include <iostream>
#include <cstdio>
SDL_Surface *s;



Mario::Mario(void): IActor(){
	



    //printf("construct");
    this->img = IMG_Load(_MARIO1);
    if (!img) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }
    this->speed = 10;

    this->onGround = true;
    this->climbing = false;
    this->movingLeft = false;
    this->movingRight = false;

    this->grav = 1;
    this->speedY = 0;
    //SDL_Rect dstrect;

		SDL_SetColorKey( this->img, SDL_SRCCOLORKEY, SDL_MapRGB(this->img->format, 0, 255, 0));
		this->source.w = this->img->w / MARIO_FRAMES;
		this->source.h = 41;
		this->source.x = 0;
		this->source.y = 0;
    this->rect.w = this->source.w;
    this->rect.h = this->source.h;
    
    

};




void Mario::jump(){
 //this->b->fire( rect.x + rect.w/2 - b->rect.w/2 , rect.y + rect.h/2);
    //std::cout << "JUMP onGround" << onGround << "\n";
   // std::cout << "JUMP climbing" << climbing << "\n";
    if(onGround && !climbing)
    {
        std::cout << "entra al if de onGround en jump" << "\n";
        this->speedY = -10;
        onGround = false;
    }

};


void Mario::moveLeft(){
    if(rect.x > 0 && !climbing){
        rect.x = rect.x-this->speed;
    }
    //std::cout << "onGround" << onGround << "\n";
    //std::cout << "climbing" << climbing << "\n";
    //fflush(std::cout);
};

void Mario::moveRight(){
    if(rect.x + img->w < GAME_W && !climbing){
        rect.x = rect.x+this->speed;
    }
    //std::cout << "Width" << rect.w << "\n";
};

void Mario::moveUp(){
    //if(onGround){
        rect.y = rect.y - this->speed;
        speedY = 0.0;
    //}
};

void Mario::moveDown(){
    //if(rect.y > 0){
        rect.y = rect.y + this->speed;
        speedY = 0.0;
   // }
};


void Mario::update(){
//std::cout << "update Mario" << " \n";
    if (movingLeft) {
        if(rect.x > 0 && !climbing){
            rect.x = rect.x-this->speed;
        }
    }
    if (movingRight) {
        if(rect.x + img->w < GAME_W && !climbing){
            rect.x = rect.x+this->speed;
        }
    }

    /*if (movingUp) {
    //if(onGround){
        rect.y = rect.y - this->speed;
        speedY = 0.0;
    //}
    }

    if (movingDown) {
    //if(rect.y > 0){
        rect.y = rect.y + this->speed;
        speedY = 0.0;
   // }
    }*/

    //jump
    if(!onGround && !climbing){
        this->speedY = this->speedY+this->grav;
        rect.y += this->speedY;
    }

}

void Mario::blit(){
    
    //std::cout << speedY << "\n";
    //positionX += velocityX;


    /*if(rect.y > GAME_H-30){
        rect.y = GAME_H-30;
        speedY = 0.0;
        onGround = true;
    }*/
    SDL_BlitSurface(this->img, &(this->source), screen, &this->rect);
    
};

void Mario::free(){
    SDL_FreeSurface(img);
}

void Mario::position(int x, int y){
    //rect.x = (screen->w - this->img->w) / 2;
    //rect.y = (screen->h - this->img->h) / 2;
    rect.x = x;
    rect.y = y;
};

void Mario::setImage(const char * str){
    this->img = IMG_Load(str);
    if (!img){ 
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
};

void Mario::setMode(int mode){
	if(mode==1){
		this->img = IMG_Load(_MARIO1);
		if (!img) 
		    printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
	if(mode==2){
		this->img = IMG_Load(_MARIO2);
		if (!img) 
		    printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
};

int Mario::getX(){
    return this->rect.x;
}

int Mario::getY(){
    return this->rect.y;
}

std::string Mario::toString(){

    std::stringstream ss;
    //std::string ret;

    ss << this->rect.x;
    ss << ",";
    ss << this->rect.y;
    ss << "\n";

    return ss.str();
};


void Mario::updateState(std::string s){
    std::stringstream f(s);
    std::stringstream ss;
    std::string r;
    int px,py;

    std::getline(f, r, ',');
    std::stringstream ( r ) >> px;
    //printf("x: %d \n", px);

    std::getline(f, r, ',');
    std::stringstream ( r ) >> py;
    //printf("y: %d \n", py);

    this->rect.x = px;
    this->rect.y = py;
};
