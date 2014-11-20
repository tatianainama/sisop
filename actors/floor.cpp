#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <stdio.h>
#include "../constants.h"
#include "floor.h"



Floor::Floor(int x, int y, int orientation) {

	/*
    this->bmp = SDL_LoadBMP("img/floor.bmp");
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }
*/	
	this->bmp = loadImage("img/piso.png");
		

    int dist = 90;
        //SDL_BlitSurface(this->bmp, 0, screen, &this->rect[i]);
    int posY = y;
    for(int i=0;i<Floor::SHIPS_QTY;i++){

        this->rect[i].x = x;
        this->rect[i].y = posY;
        this->rect[i].w = 800;
        this->rect[i].h = 15;
                    
        posY += dist;
    }
            //row++;
    
};



void Floor::update(){

};

void Floor::blit(){


    //SDL_BlitSurface(this->bmp, 0, screen, &rect);

    for (int j=0;j<Floor::SHIPS_QTY;j++) {
       //if(shipsf[j] == 1) {
            SDL_BlitSurface(this->bmp, 0, screen, &rect[j]);
        //}
    }

    // printf("%d \n",t.get_ticks());
    /*SDL_BlitSurface(this->bmp, 0, screen, &this->rect1);
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect2);
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect3);*/
};


SDL_Rect * Floor::getNextBaseFloor(int y){

    for (int i=0;i<Floor::SHIPS_QTY;i++) {        
        if(this->rect[i].y > y){
            return &this->rect[i];
        }
    }
    return NULL;

};




void Floor::free(){
    SDL_FreeSurface(bmp);
}

void Floor::position(int x, int y){
    //rect.x = (screen->w - this->bmp->w) / 2;
    //rect.y = (screen->h - this->bmp->h) / 2;
    /*rect.x = x;
    rect.y = y;*/
    //printf("dsadas \n");
    //printf("%d",gNum);
};


std::string Floor::toString(){

    std::stringstream ss;
    //std::string ret;
/*

    for(int i=0;i< Floor::SHIPS_QTY;i++){
        ss << shipsf[i];
        if(i != Floor::SHIPS_QTY -1){
            ss << ",";
        }
    }
    ss << "\n";
*/
    ss << 0;
    ss << "\n";
    return ss.str();

};

SDL_Surface* Floor::loadImage(const char* path){
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

void Floor::updateState(std::string s){
   /* std::istringstream f(s);
    std::stringstream ss;
    std::string segment;
    //int x,y;
    int stat;

    //std::getline(f, segment, '|');

    //std::istringstream ( segment ) >> stat;

    for(int i=0;i< Floor::SHIPS_QTY;i++){
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
