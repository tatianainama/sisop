#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <stdio.h>
#include "../constants.h"
#include "bonus.h"
#include <iostream>


Bonus::Bonus(int x, int y) {

   /* this->bmp = SDL_LoadBMP("img/bonus.bmp");
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }*/
    
    this->bmp = loadImage("img/bonus.png");

    state = 1;
    //climbing = false;
    speed = 4;
    speedY = 4;
    dir =1;
    moveQty =0;
    //int startY = 300;
    /* initialize random seed: */
    srand (time(NULL));

    int posX = x;
    int posY = y;
    //int posY = 400;
    int perRow = 7;
    int row =0;
    int dist = 70;
    int distY= 70;

    /*this->rect.x = posX;
    this->rect.y = posY;
    this->rect.w = 30;*/
            //printf()


    for(int i=0;i<Bonus::SHIPS_QTY;i++){
        this->rect[i].x = posX;
        this->rect[i].y = posY;                    
        this->rect[i].w = 30;
        this->rect[i].h = 30;

        shipsf[i] = 0;
        if(i % 2 ==0){
            speedf[i] = 4;
        }else{
            speedf[i] = -4;
        }
        climbing[i] = false;
    }

    shipsf[0] = 1;

   // t.stop();
    t.start();
    std::cout << "arranco reloj " << " \n";

};



void Bonus::moveLeft(){
   /* if(rect.x > 0){
        rect.x = rect.x-speed;
    } else {
        this->reset();
    }*/
};

void Bonus::moveRight(){

      /*
      if(rect.x + rect.w < GAME_W){
            rect.x += speed;
        }else{
            this->reset();
        }
        */
};

void Bonus::move(int i){
        
        if( rect[i].x+ rect[i].w > GAME_W || rect[i].x < 1){
            //std::cout << "entra al if de move" << "\n";
            //std::cout << "data: " << rect.x  << "\n";
            if(rect[i].y > GAME_H -50){
                this->reset(i);
                return;
            }
            speedf[i] = speedf[i] * -1;
        }
        rect[i].x += speedf[i];
        //std::cout << "Speed de i=" << i << " :"<< this->speedf[i] << " \n";
};


void Bonus::moveDown(int i){
    //if(rect.y > 0){
        rect[i].y = rect[i].y + speedY;
       //speedY = 0.0;
   // }
};

void Bonus::reset(int i){

    this->shipsf[i] = 0;
    this->rect[i].x = GAME_W / 2;
    this->rect[i].y = 108;

}


void Bonus::update(){
    
    if(t.get_ticks() > 1500){
        //std::cout << "entra al if de bonus" << " \n";

        for(int i=0;i< Bonus::SHIPS_QTY;i++){            
            if(shipsf[i]==0){
                shipsf[i]=1;
                break;
            }
        }

        t.stop();
        t.start();
    }


    for(int i=0;i< Bonus::SHIPS_QTY;i++){            
        if(shipsf[i]==1){
            if(climbing[i]){
                this->moveDown(i);
            } else {
                this->move(i);    
            }
        }
    }

//std::cout << "sale del if de bonus" << " \n";    

}

void Bonus::blit(){

            //}
               
    for(int i=0;i< Bonus::SHIPS_QTY;i++){     
        if(shipsf[i] ==1){
            SDL_BlitSurface(this->bmp, 0, screen, &rect[i]);
        }
    }
           

    //}
    // printf("%d \n",t.get_ticks());
    /*SDL_BlitSurface(this->bmp, 0, screen, &this->rect1);
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect2);
    SDL_BlitSurface(this->bmp, 0, screen, &this->rect3);*/
};

void Bonus::free(){
    SDL_FreeSurface(bmp);
}

void Bonus::position(int x, int y){

    //rect.x = (screen->w - this->bmp->w) / 2;
    //rect.y = (screen->h - this->bmp->h) / 2;
    /*rect.x = x;
    rect.y = y;*/
    //printf("dsadas \n");
    //printf("%d",gNum);
};


int Bonus::getX(){
 //return this->rect.x;
 return 1;
}

int Bonus::getY(){
 //return this->rect.y;
 return 1;
}


std::string Bonus::toString(){

    std::stringstream ss;


    //std::string ret;
    //ss << this->rect[0].x;
    //ss << ",";
    //ss << this->rect[0].y;
    //ss <<  "|";

    for(int i=0;i< Bonus::SHIPS_QTY;i++){
        ss << shipsf[i];
        ss << ",";
        ss << rect[i].x;
        ss << ",";
        ss << rect[i].y;

        if(i != Bonus::SHIPS_QTY -1){
            ss <<  "|";
            //ss << ",";
        }
    }
    ss << "\n";

    return ss.str();
};




void Bonus::updateState(std::string s){
    
    //std::cout << "\n" << s << "\n";
    std::stringstream ss(s);
    //std::stringstream ss;
    std::string segment;
    std::stringstream s2;    
    std::string dat;
    int x,y;
    int status;


    for(int i=0;i<Bonus::SHIPS_QTY;i++){
        std::getline(ss, segment, '|');

        //std::cout << segment;
        //std::cout << "\n";
        s2 << segment;
        std::getline(s2, dat, ',');
        std::istringstream ( dat ) >> status;
        //std::cout << dat;
        //std::cout << "\n";

        std::getline(s2, dat, ',');
        std::istringstream ( dat ) >> x;
        //std::cout << dat;
        //std::cout << "\n";

        std::getline(s2, dat, ',');
        std::istringstream ( dat ) >> y;
        //std::cout << dat;
        //std::cout << "seteo al i="<<i << "con datos: " << status << "," << x << "," << y <<"\n";
        shipsf[i] = status;
        rect[i].x = x;
        rect[i].y = y;

        s2.str("");
        s2.clear();
        //ss.str(std::string());
    }
};
SDL_Surface* Bonus::loadImage(const char* path){
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



