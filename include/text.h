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
        
        void init(font_t f, texture_t t);
        void setPosition(int xp, int yp);
        void setText(std::string text);
        void loadTexture(SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer);
        void free();
        
        font_t font;
        texture_t texture;
        std::string name;
        std::string text;
        int x, y;
        int w, h;
};

