#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>

class texture_t{
    public:
		texture_t();
		~texture_t();
		bool loadFromFile(std::string path, SDL_Renderer* renderer);
		void free();
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(Uint8 alpha);
		void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);
		int getWidth();
		int getHeight();
        std::string getLocation();

	private:
		SDL_Texture* mTexture;

        std::string location;
		int width;
		int height;
    
};
