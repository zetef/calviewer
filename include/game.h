#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "constants.h"
#include "texture.h"
#include "state.h"

class game_t{
    public:
        game_t(std::string title);
        ~game_t();
        
        std::string name;
        SDL_Window* window;
        SDL_Renderer* renderer;
        state_t state;
        
        bool init();
        
    private:
        void free();
};
