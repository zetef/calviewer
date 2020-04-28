#include "../include/Font.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Font::Font(){
	m_font = NULL;
	m_path = "./";
	m_size = 10;
	m_color.r = 0;
	m_color.g = 0;
	m_color.b = 0;
	m_color.a = 255;
}

Font::~Font(){
	free();
}

void Font::init(std::string t_path, int t_size, SDL_Color t_color){
	m_path = t_path;
	m_size = t_size;
	m_color = t_color;
}

void Font::set_path(std::string t_path){
	m_path = t_path;
}

void Font::set_size(int t_size){
	m_size = t_size;
}

void Font::set_color(SDL_Color t_color){
	m_color = t_color;
}

TTF_Font* Font::get_font(){
	return m_font;
}

std::string Font::get_path(){
	return m_path;
}

int Font::get_size(){
	return m_size;
}

SDL_Color Font::get_color(){
	return m_color;
}

bool Font::is_null(){
	return m_font == NULL;
}

bool Font::load(){
	bool success = true;

	std::string path = "./res/fonts/" + m_path;
	m_font = TTF_OpenFont(path.c_str(), m_size);
	if(m_font == NULL){
		printf("failed to load font from file \"%s\". error: %s\n", path.c_str(), TTF_GetError());
		success = false;
	}

	return success;
}

void Font::free(){
	if(m_font != NULL){
		TTF_CloseFont(m_font);
		m_font = NULL;
		m_path = "./";
		m_size = 0;
		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 0;
		m_color.a = 255;
	}
}

////////////////////////////////
