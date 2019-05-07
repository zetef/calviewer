#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Text.h"
#include "Texture.h"
#include "Font.h"
#include "utility.h"

class Media{
	public:
		
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////
		
		//clears the two maps
		Media();
		
		//frees all the textures and fonts allocated
		~Media();
		
		//loads the textures and fonts into the maps
		bool load(SDL_Renderer* t_renderer);
		
		//renders a specified texture with the following properties
		void render(SDL_Renderer* t_renderer, std::string t_name, int t_x, int t_y, SDL_Rect* t_clip = NULL, double t_angle = 0.0f, SDL_Point* t_center = NULL, SDL_RendererFlip t_flip = SDL_FLIP_NONE);
		
		//frees all the allocated memory
		void free();
		
		//returns the texture map
		std::map<std::string, Texture>* get_textures();

		//returns the fonts map
		//std::map<std::string, Font>* get_fonts();
		
		//prints to stdout the textures it loaded
		void show_textures();
		
		//prints to stdout the fonts it loaded
		//void show_fonts();
    
		////////////////////////////////
		
	private:
		
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////
		
		std::map<std::string, Texture> m_textures;
		//std::map<std::string, Font>    m_fonts;
		
		////////////////////////////////
};
