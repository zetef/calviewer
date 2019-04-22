#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "texture.h"

class media_t{
    public:
        media_t();
        ~media_t();
        
        std::map<std::string, texture_t> textures;
        TTF_Font* hbold;
        TTF_Font* hlight;
        
        bool load(SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer, std::string name, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0f, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        void showTextures();
    
    private:
        void free();
    
};
