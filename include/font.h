#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include "utility.h"

class font_t{
    public:
        font_t();
        ~font_t();
        
        void init(std::string p, int s, SDL_Color c);
        bool load();
        void free();
        
        TTF_Font* font;
        std::string name;
        std::string path;
        int size;
        std::string text;
        SDL_Color color;
};
