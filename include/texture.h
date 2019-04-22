#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>

class texture_t{
    public:
		texture_t();
		~texture_t();
		bool loadFromFile(SDL_Renderer* renderer, std::string path);
#ifdef _SDL_TTF_H
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);
#endif
		
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(Uint8 alpha);
		void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		int getWidth();
		int getHeight();
        void setLocation(std::string path);
        std::string getLocation();
        
        void free();

	private:
		SDL_Texture* mTexture;

        std::string location;
		int width;
		int height;
    
};
