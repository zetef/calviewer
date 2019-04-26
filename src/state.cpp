#include "../include/state.h"

state_t::state_t(){
    init();
}

state_t::~state_t(){
    free();
}

void state_t::init(){
    quit = false;
}

void state_t::handle(calendar_t* calendar){ //TODO take care of overflows
    while (SDL_PollEvent(&event) != 0){
        if (event.type == SDL_QUIT){
            quit = true;
        } else if (event.key.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            } else if(event.key.keysym.sym == SDLK_LEFT){
                if(calendar->m - 1 < 0){
                    calendar->m = 11;
                    calendar->y--;
                } else
                    calendar->m--;
                calendar->generate();
            } else if(event.key.keysym.sym == SDLK_RIGHT){
                if(calendar->m + 1 > 11){
                    calendar->m = 0;
                    calendar->y++;
                } else 
                    calendar->m++;
                calendar->generate();
            }
        }
    }
}

void state_t::free(){
    quit = false;
}
