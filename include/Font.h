#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include "utility.h"

class Font{
	public:

		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////

		//constructor defaults all variables
		Font();

		//frees all the memory used by TTF_Font*
		~Font();

		//initializes the font with these properties
		void init(std::string t_path, int t_size, SDL_Color t_color); //TODO: implement the setters as well

		//sets the font path
		void set_path(std::string t_path);
		
		//sets the font size
		void set_size(int t_size);
		
		//sets the font color
		void set_color(SDL_Color t_color);
		
		//returns the font it uses
		TTF_Font* get_font();

		//returns the path the font is from
		std::string get_path();

		//returns the size of the font when rendered
		int get_size();

		//returns the color of the font when rendered
		SDL_Color get_color();
		
		bool is_null();

		//loads the font itself into TTF_Font*
		bool load();

		//closes the font and destructs the pointer
		void free();

		////////////////////////////////

	private:

		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////

		TTF_Font*   m_font;  //the font it uses
		std::string m_path;  //the path of the font
		int         m_size;  //the size in pixels of the font
		SDL_Color   m_color; //the color of the font

		////////////////////////////////

};
