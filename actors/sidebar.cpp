
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <stdio.h>
#include "../constants.h"
#include "sidebar.h"



SideBar::SideBar(void){
    //printf("construct");

    if (TTF_Init() == -1)
  {
    printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
    exit(1);
  }

	this->font = TTF_OpenFont(_FONT,_FONT_SIZESB);
	if (this->font == NULL){
	  printf("Unable to load font: %s %s \n", _FONT, TTF_GetError());
	  // Handle the error here.
	}
	this->sidebar = SDL_LoadBMP("img/sidebar.bmp");
    if (!this->sidebar) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
        exit(1);
    }
    this->ship1 = SDL_LoadBMP(_SHIP1);
    if (!ship1) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }
    this->ship2 = SDL_LoadBMP(_SHIP2);
    if (!ship1) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        //return 1;
    }

	this->fontColor1.r = 0;
	this->fontColor1.g = 255;
	this->fontColor1.b = 0;
	this->fontColor2.r = 0;
	this->fontColor2.g = 0;
	this->fontColor2.b = 255;
	this->rectSideBar.x=800;
	this->rectSideBar.y=0;
	this->rectName1.x=this->rectName2.x=this->rectScore1.x=this->rectScore2.x=this->rectLife1.x=this->rectLife2.x=810;

	int i = _SEPARATIONSB;
	this->rectName2.y= i;
	this->rectScore2.y= i+20;
	this->rectLife2.y = i+60;

    this->rectName1.y= GAME_H-i-60;
    this->rectScore1.y= GAME_H-i-40;
	this->rectLife1.y = GAME_H-i;


    setName1("Player 1");
    setName2("Player 2");
    setLife1(4);
    setLife2(4);
    setScore1(0);
    setScore2(0);

};

void SideBar::setName1(const char name[60]){
	strcpy(this->Name1,name);
	this->text_name1 = TTF_RenderText_Blended(this->font,this->Name1, fontColor1);
};
void SideBar::setName2(const char name[60]){
	strcpy(this->Name2,name);
	this->text_name2 = TTF_RenderText_Blended(this->font,this->Name2, fontColor2);
};

void SideBar::setScore1(int scr){
	this->Score1=scr;
    char temp[20];
	sprintf(temp,"P: %02d",this->Score1);
	this->text_score1 = TTF_RenderText_Blended(this->font,temp, fontColor1);
};
void SideBar::setScore2(int scr){
	this->Score2=scr;
	char temp[20];
	sprintf(temp,"P: %02d",this->Score2);
	this->text_score2 = TTF_RenderText_Blended(this->font,temp, fontColor2);
};

void SideBar::setLife1(int life){
	this->Life1=life;
	char temp[20];
	sprintf(temp,"   X %d",this->Life1);
	this->text_life1 = TTF_RenderText_Blended(this->font,temp, fontColor1);
};
void SideBar::setLife2(int life){
	this->Life2=life;
	char temp[20];
	sprintf(temp,"   X %d",this->Life2);
	this->text_life2 = TTF_RenderText_Blended(this->font,temp, fontColor2);
};

char* SideBar::getName1(){
    return this->Name1;
};
char* SideBar::getName2(){
    return this->Name2;
};
int SideBar::getLife1(){
    return this->Life1;
};
int SideBar::getLife2(){
    return this->Life2;
};
int SideBar::getScore1(){
    return this->Score1;
};
int SideBar::getScore2(){
    return this->Score2;
};

void SideBar::addToScore1(int points){
    int newScore = points + this->Score1;
    setScore1(newScore);
};
void SideBar::addToScore2(int points){
    int newScore = points + this->Score2;
    setScore2(newScore);
};

void SideBar::addToLife1(int life){
    int newLife = life + this->Life1;
    setLife1(newLife);
};
void SideBar::addToLife2(int life){
    int newLife = life + this->Life2;
    setLife2(newLife);
};

void SideBar::update(){

};

void SideBar::blit(){
    SDL_BlitSurface(this->sidebar, NULL, screen, &this->rectSideBar);
    SDL_BlitSurface(this->text_name1, NULL, screen, &this->rectName1);
	SDL_BlitSurface(this->text_name2, NULL, screen, &this->rectName2);
	SDL_BlitSurface(this->text_score1, NULL, screen, &this->rectScore1);
	SDL_BlitSurface(this->text_score2, NULL, screen, &this->rectScore2);

/*
	SDL_BlitSurface(this->ship1, NULL, screen, &this->rectLife1);
	if (this->Life1>3 || this->Life1 == 0){
	SDL_BlitSurface(this->text_life1, NULL, screen, &this->rectLife1);
	}
	else{
	    if(this->Life1>1){
        tempMario.y=rectLife1.y;
        tempMario.x=rectLife1.x+25;
        SDL_BlitSurface(this->ship1, NULL, screen, &this->tempMario);
        }
        if(this->Life1>2){
            tempMario.x+=25;
            SDL_BlitSurface(this->ship1, NULL, screen, &this->tempMario);
        }

    }

    SDL_BlitSurface(this->ship2, NULL, screen, &this->rectLife2);
	if (this->Life2>3 || this->Life2 == 0){
	SDL_BlitSurface(this->text_life2, NULL, screen, &this->rectLife2);
	}
	else{
	    if(this->Life2>1){
        tempMario.y=rectLife2.y;
        tempMario.x=rectLife2.x+25;
        SDL_BlitSurface(this->ship2, NULL, screen, &this->tempMario);
        }
        if(this->Life2>2){
            tempMario.x+=25;
            SDL_BlitSurface(this->ship2, NULL, screen, &this->tempMario);
        }

    }
*/

};

void SideBar::free(){
    SDL_FreeSurface(this->sidebar);
    SDL_FreeSurface(this->text_name1);
	SDL_FreeSurface(this->text_name2);
	SDL_FreeSurface(this->text_score1);
	SDL_FreeSurface(this->text_score2);
	SDL_FreeSurface(this->text_life1);
	SDL_FreeSurface(this->text_life2);
}

void SideBar::position(int x, int y){
    rectSideBar.x = x;
    rectSideBar.y = y;
};


int SideBar::getX(){
 return this->rectSideBar.x;
}

int SideBar::getY(){
 return this->rectSideBar.y;
}


std::string SideBar::toString(){

    std::stringstream ss;
    //std::string ret;

    //ss << this->state;
    //ss << "|";

    ss << this->getLife1();
    ss << ",";
    ss << this->getScore1();
    ss << ",";
    ss << this->getLife2();
    ss << ",";
    ss << this->getScore2();
    ss << "\n";

    return ss.str();
};

void SideBar::updateState(std::string s){
    std::istringstream f(s);
  //  std::stringstream ss;
    std::string segment;

    int v1,v2;
    int sc1,sc2;

    std::getline(f, segment, ',');
    std::istringstream ( segment ) >> v1;


    std::getline(f, segment, ',');
    std::istringstream ( segment ) >> sc1;
    //printf("x: %d \n", x);

    std::getline(f, segment, ',');
    std::istringstream ( segment ) >> v2;
    //printf("y: %d \n", y);

    std::getline(f, segment, ',');
    std::istringstream ( segment ) >> sc2;

    this->setLife1(v1);
    this->setLife2(v2);

    this->setScore1(sc1);
    this->setScore2(sc2);
};
