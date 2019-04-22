#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "constants.h"
#include "texture.h"
#include "state.h"

class game_t{
    public:
        game_t(std::string title);
        ~game_t();
        
        state_t state;
        
        std::string getName();
        SDL_Renderer* getRenderer();
        
        bool init();
        bool loadMedia();
        void render(texture_t* texture, int x, int y, SDL_Rect* clip = NULL);
        
        unsigned int getThroughTexturesUntil(std::string path);
        texture_t* getTexture(std::string path);
        void showTextures();
        void addTexture(texture_t* texture);
        void removeTexture(texture_t* texture);
        
    private:
        std::string name;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<texture_t*> textures;
        
        unsigned int getThroughTexturesUntil(texture_t* texture);
        texture_t* getTexture(texture_t* texture);
        void free();
};
