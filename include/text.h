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
        void setPosition(int xpos, int ypos);
        void setClip(SDL_Rect* clip); 
        void setAngle(double a);
        void setCenter(SDL_Point* point);
        void setFlip(SDL_RendererFlip f);
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
        SDL_Rect renderQuad;
        double angle;
        SDL_Point* center;
        SDL_RendererFlip flip;
};

