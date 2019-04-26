#pragma once

#include <SDL.h>
#include <stdio.h>

#include "calendar.h"

class state_t{
    public:
        state_t();
        ~state_t();
        void init();
        void handle(calendar_t* calendar);
        SDL_Event event;
        bool quit;
        void free();
};
