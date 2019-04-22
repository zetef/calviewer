#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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
        TTF_Font* font;
        state_t state;
        std::map<std::string, texture_t> textures;
        
        bool init();
        bool loadMedia();
        void render(texture_t texture, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0f, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        
        void showTextures();
        texture_t getTexture(std::string path);
        texture_t getTexture(texture_t texture);
        void addTexture(texture_t texture);
        void removeTexture(texture_t texture);
        
    private:
        void free();
};
