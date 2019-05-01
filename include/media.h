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
#include "font.h"
#include "text.h"
#include "utility.h"

class media_t{
    public:
        media_t();
        ~media_t();
        
        std::map<std::string, texture_t> textures;
        std::map<std::string, font_t> fonts;
        std::map<std::string, text_t> texts;
        
        bool load(SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer, std::string name, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0f, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        void showTextures();
    
    private:
        void free();
    
};
