#include "../include/timer.h"

timer_t::timer_t(){
    startTicks = 0;
    pausedTicks = 0;
    
    paused = false;
    started = false;
}

void timer_t::start(){
    started = true;
    paused = false;
    
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void timer_t::stop(){
    started = false;
    paused = false;
    
    startTicks = 0;
    pausedTicks = 0;
}

void timer_t::pause(){
    if(started && !paused){
        paused = true;
        
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void timer_t::unpause(){
    if(started && paused){
        paused = false;
        
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 timer_t::getTicks(){
    Uint32 time = 0;
    
    if(started){
        if(paused){
            time = pausedTicks;
        } else {
            time = SDL_GetTicks() - startTicks;
        }
    }
    
    return time;
}

bool timer_t::isStarted(){
    return started;
}

bool timer_t::isPaused(){
    return paused && started;
}
