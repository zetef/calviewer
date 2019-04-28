#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#include "texture.h"
#include "font.h"

class text_t{
    public:
        text_t();
        ~text_t();
        
        void render(SDL_Renderer* renderer, int x, int y);
        void free();
        
        font_t font;
        texture_t texture;
};

