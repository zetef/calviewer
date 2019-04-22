#include "../include/state.h"

state_t::state_t(){
    printf("initializing state...\n");
    init();
    printf("state initialized!\n\n");
}

state_t::~state_t(){
    printf("destructing state...\n");
    free();
    printf("state destructed!\n\n");
}

void state_t::init(){
    quit = false;
}

void state_t::handle(){
    while ( SDL_PollEvent( &event ) != 0 ) {
        if ( event.type == SDL_QUIT ) {
            quit = true;
        } else if ( event.key.type == SDL_KEYDOWN ) {
            if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                quit = true;
            }
        }
    }
}

void state_t::free(){
    quit = false;
}
