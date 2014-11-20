#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <stdio.h>
#include "../constants.h"
#include "monkey.h"
#include <iostream>
#include <cstdio>




Monkey::Monkey(void): IActor(){
    //printf("construct");
    /*this->bmp = SDL_LoadBMP("img/monkey.bmp");
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }*/
    
    this->bmp = loadImage("img/monkey.png");
    this->speed = 10;

    this->onGround = true;
    this->climbing = false;
    this->grav = 1;
    this->speedY = 0;
    //SDL_Rect dstrect;
};




void Monkey::jump(){
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


void Monkey::moveLeft(){
    if(rect.x > 0 && !climbing){
        rect.x = rect.x-this->speed;
    }
    //std::cout << "onGround" << onGround << "\n";
    //std::cout << "climbing" << climbing << "\n";
    //fflush(std::cout);
};

void Monkey::moveRight(){
    if(rect.x + bmp->w < GAME_W && !climbing){
        rect.x = rect.x+this->speed;
    }
    //std::cout << "Width" << rect.w << "\n";
};

void Monkey::moveUp(){
    //if(onGround){
        rect.y = rect.y - this->speed;
        speedY = 0.0;
    //}
};

void Monkey::moveDown(){
    //if(rect.y > 0){
        rect.y = rect.y + this->speed;
        speedY = 0.0;
   // }
};


void Monkey::update(){
//std::cout << "update monkey" << " \n";
    if(!onGround && !climbing){
        this->speedY = this->speedY+this->grav;
        rect.y += this->speedY;
    }

}

void Monkey::blit(){
    
    //std::cout << speedY << "\n";
    //positionX += velocityX;


    /*if(rect.y > GAME_H-30){
        rect.y = GAME_H-30;
        speedY = 0.0;
        onGround = true;
    }*/
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect);
};

void Monkey::free(){
    SDL_FreeSurface(bmp);
}

void Monkey::position(int x, int y){
    //rect.x = (screen->w - this->bmp->w) / 2;
    //rect.y = (screen->h - this->bmp->h) / 2;
    rect.x = x;
    rect.y = y;
};


void Monkey::setMode(int mode){
	if(mode==1){
		//this->bmp = SDL_LoadBMP(_MMONKEY1);
		if (!bmp) 
		    printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
	if(mode==2){
		//this->bmp = SDL_LoadBMP(_MMONKEY2);
		if (!bmp) 
		    printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
};

int Monkey::getX(){
    return this->rect.x;
}

int Monkey::getY(){
    return this->rect.y;
}

std::string Monkey::toString(){

    std::stringstream ss;
    //std::string ret;

   /* ss << this->rect.x;
    ss << ",";
    ss << this->rect.y;*/

    ss << "0";
    ss << "\n";

    return ss.str();
};


void Monkey::updateState(std::string s){
    /*std::istringstream f(s);
    std::stringstream ss;
    std::string r;
    int px,py;

    std::getline(f, r, ',');
    std::istringstream ( r ) >> px;
    //printf("x: %d \n", px);

    std::getline(f, r, ',');
    std::istringstream ( r ) >> py;
    //printf("y: %d \n", py);

    this->rect.x = px;
    this->rect.y = py;*/
};

SDL_Surface* Monkey::loadImage(const char* path){
	SDL_Surface*opt, *img;
	img = IMG_Load(path);
  if (!img) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
        return NULL;
  }
	opt = SDL_DisplayFormat(img);
	SDL_FreeSurface(img);
	SDL_SetColorKey( opt, SDL_SRCCOLORKEY, SDL_MapRGB(opt->format, 0, 255, 0));
	return opt;
}

