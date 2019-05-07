#include "../include/State.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

State::State(){
    init();
}

State::~State(){
    free();
}

void State::init(){
    m_quit = false;
}

void State::handle(Calendar* t_calendar){ //TODO take care of overflows. DONE: problem is the 2038 overflow. affects only 32-bit systems
    while (SDL_PollEvent(&m_event) != 0){
        if (m_event.type == SDL_QUIT){
            m_quit = true;
        } else if (m_event.key.type == SDL_KEYDOWN){
            if (m_event.key.keysym.sym == SDLK_ESCAPE){
                m_quit = true;
            }
        }
        t_calendar->handle_event(&m_event);
    }
    
}

SDL_Event State::get_event(){
	return m_event;
}

bool State::get_quit(){
	return m_quit;
}

void State::free(){
    m_quit = false;
}

////////////////////////////////
