#ifdef _IACTOR

#else

#define _IACTOR 1
#include <SDL/SDL.h>
#include <string>
class IActor{

    public:
        virtual void blit()=0;

        virtual void update()=0;

        virtual void free()=0;

        bool checkCollision(SDL_Rect, SDL_Rect);

        virtual std::string toString()=0;

        virtual void updateState(std::string)=0;
};

#endif

