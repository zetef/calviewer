#pragma once

#include <SDL.h>

class state_t{
    public:
        state_t();
        ~state_t();
        void init();
        void handle();
        SDL_Event event;
        bool quit;
        
    private:
        
        void free();
};
