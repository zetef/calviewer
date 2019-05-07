#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Font.h"

class Texture{
	public:

		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////

		//constructor defaults all variables
		Texture();

		//frees the texture it uses if not NULL
		~Texture();

		//loads from file texture
		bool load_from_file(SDL_Renderer* t_renderer, std::string t_path);

		//loads text from a font
		bool load_from_rendered_text(SDL_Renderer* t_renderer, Font* t_font, std::string t_text);

		//sets the tone of the texture (color modulation)
		void set_color(Uint8 t_red, Uint8 t_green, Uint8 t_blue);

		//sets blend mode of the texture
		void set_blend_mode(SDL_BlendMode t_blending);

		//sets the alpha of the texture
		void set_alpha(Uint8 t_alpha);

		//renders the texture with the following properties
		void render(SDL_Renderer* t_renderer, int t_x, int t_y, SDL_Rect* t_clip = NULL, double t_angle = 0.0, SDL_Point* t_center = NULL, SDL_RendererFlip t_flip = SDL_FLIP_NONE);

		//returns the width of the texture
		int get_width();

		//returns the height of the texture
		int get_height();

		//returns the path of the image file loaded into the texture
		std::string get_path();

		//frees allocated memory for SDL_Texture*
		void free();

		////////////////////////////////

	private:

		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////

		SDL_Texture* m_texture; //the texture itself
		std::string  m_path;    //the path of the image that is loaded(if any, texture can be used for Text class)
		int          m_width;   //the width of the texture
		int          m_height;  //the height of the texture

		////////////////////////////////

};
