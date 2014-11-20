#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <stdio.h>
#include "../constants.h"
#include "stairs.h"
#include <iostream>



Stairs::Stairs(int x, int y, int orientation) {

    /*this->bmp = SDL_LoadBMP("img/stairs.bmp");
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }*/
    
    this->bmp = loadImage("img/stairs.png");

    int startX = x;
    int startY = y;

    int posX = startX;
    int posY = startY;
    int perRow = 2;
    int row =0;
    int dist = 510;
    int distY= 90;

    std::cout << "j";

    int despl = 100;


    for(int i=0;i<Stairs::SHIPS_QTY;i++){
        this->rect[i].w = 36;
        this->rect[i].h = 90; 
        if(i == 4 ||  i == 7){
            posY += distY;
            posX = GAME_W /2;
            this->rect[i].x = posX;
            this->rect[i].y = posY; 

            posX = startX;              
            posY += distY;

        } else if(i== 0){
            this->rect[i].x = GAME_W /2 -100;
            this->rect[i].y = posY;
            posX += dist;
        }else if( i==1) {
            this->rect[i].x = GAME_W /2 +100;
            this->rect[i].y = posY;
            posX = startX;
            posY +=distY;
        } else{
            this->rect[i].x = posX;
            this->rect[i].y = posY;
            posX += dist;
        }

    }
};




void Stairs::update(){

};


void Stairs::blit(){

    for (int j=0;j<Stairs::SHIPS_QTY;j++) {
       //if(shipsf[j] == 1) {
            SDL_BlitSurface(this->bmp, 0, screen, &rect[j]);
        //}
    }
    // printf("%d \n",t.get_ticks());
    /*SDL_BlitSurface(this->bmp, 0, screen, &this->rect1);
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect2);
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect3);*/
};

void Stairs::free(){
    SDL_FreeSurface(this->bmp);
}

void Stairs::position(int x, int y){
    //rect.x = (screen->w - this->bmp->w) / 2;
    //rect.y = (screen->h - this->bmp->h) / 2;
    /*rect.x = x;
    rect.y = y;*/
    //printf("dsadas \n");
    //printf("%d",gNum);
};


std::string Stairs::toString(){

    std::stringstream ss;


    //std::string ret;

/*
    for(int i=0;i< Stairs::SHIPS_QTY;i++){
        ss << shipsf[i];
        if(i != Stairs::SHIPS_QTY -1){
            ss << ",";
        }
    }
    
*/
    ss << "0";
    ss << "\n";
    return ss.str();

};

SDL_Surface* Stairs::loadImage(const char* path){
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

void Stairs::updateState(std::string s){
   /* std::stringstream f(s);
    std::stringstream ss;
    std::string segment;
    //int x,y;
    int stat;

    //std::getline(f, segment, '|');

    //std::istringstream ( segment ) >> stat;

    for(int i=0;i< Stairs::SHIPS_QTY;i++){
        std::getline(f, segment, ',');
        std::istringstream ( segment ) >> stat;
        //printf("x: %d \n", stat);
        shipsf[i] = stat;
    }
/*
    std::getline(f, segment, ',');
    std::istringstream ( segment ) >> x;
    printf("x: %d \n", x);

    std::getline(f, segment, ',');
    std::istringstream ( segment ) >> y;
    printf("y: %d \n", y);

    this->state = stat;
    this->rect.x = x;
    this->rect.y = y;
    */
};
