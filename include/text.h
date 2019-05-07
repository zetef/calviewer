#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Texture.h"
#include "Font.h"

class Text{
	public:
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////

		//constructor sets values to default
		Text();

		//destructor frees the font and texture memory
		~Text();

		//creates copies of these font and texture to the members
		void init(Font t_font, Texture t_texture);

		//changes currently used font to t_font
		void change_font(Font t_font);
		
		//frees the texture so new text can be written so no more memory leaks
		void reload();
		
		//returns the font that this text uses
		Font* get_font();

		//returns the texture that this text uses
		Texture* get_texture();

		//sets position of the text on screen
		void set_position(int t_xpos, int t_ypos);

		//returns x position of the text on screen
		int get_x();

		//returns y position of the text on screen
		int get_y();
		
		//returns the width of the text
		int get_width();
		
		//returns the height of the text
		int get_height();

		/* //TODO: implement clip feature
		//portion of the text to be shown
		void set_clip(SDL_Rect* t_clip); 

		//returns the clip of the image
		SDL_Rect get_clip();
		*/

		//angle at which it will rendered
		void set_angle(double t_angle);

		//returns angle
		double get_angle();

		//center to rotate around
		void set_center(SDL_Point* t_center);

		//returns center
		SDL_Point* get_center();

		//flip mode, vertical, horizontal, none
		void set_flip(SDL_RendererFlip t_flip);

		//returns flip mode
		SDL_RendererFlip get_flip();

		//sets the text
		void set_text(std::string t_text);
		
		std::string get_text();
		
		//loads the texture
		void load_texture(SDL_Renderer* t_renderer);

		//sets text and loads the texture; it accepts any value
		template<typename T>
		void set_and_load(SDL_Renderer* t_renderer, T t_value);

		//renders the text with the above mentioned properties
		void render(SDL_Renderer* t_renderer);

		//defaults variables, closes the font and frees the texture
		void free();

		////////////////////////////////

	private:
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////

		Font             m_font;            //font that will be used for text
		Texture          m_texture;         //texture that will hold the text
		std::string      m_text;            //the text that will be rendered
		int              m_x, m_y;          //the position of the text
		int              m_width, m_height; //the dimensions of the text
		SDL_Rect         m_render_quad;     //the portion of the texture
		double           m_angle;           //the angle at which it will rotate
		SDL_Point*       m_center;          //the center to rotate around
		SDL_RendererFlip m_flip;            //the flip mode of the texture

		////////////////////////////////
};

//found this incovenience, might refactor it later idk
template<typename T>
void Text::set_and_load(SDL_Renderer* t_renderer, T t_value){
	std::stringstream val;
	val.str("");
	val << t_value;
	
	set_text(val.str());
	load_texture(t_renderer);
}
