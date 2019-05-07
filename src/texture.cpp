#include "../include/Texture.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Texture::Texture(){
	m_texture = NULL;
	m_path = "./res/textures/default.png";
	m_width = 0;
	m_height = 0;
}

Texture::~Texture(){
	free();
}

bool Texture::load_from_file(SDL_Renderer* t_renderer, std::string t_path){
	free();

	m_path = t_path;

	SDL_Texture* new_texture = NULL;
	
	SDL_Surface* loaded_surface = IMG_Load(t_path.c_str());
	if(loaded_surface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", t_path.c_str(), IMG_GetError());
	} else {
		SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0x00, 0xff, 0x00));

        new_texture = SDL_CreateTextureFromSurface(t_renderer, loaded_surface);
		if(new_texture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", t_path.c_str(), SDL_GetError());
		} else {
			m_width = loaded_surface->w;
			m_height = loaded_surface->h;
		}

		SDL_FreeSurface(loaded_surface);
	}

	m_texture = new_texture;
	return m_texture != NULL;
}

bool Texture::load_from_rendered_text(SDL_Renderer* t_renderer, Font* t_font, std::string t_text){
	free();
	
	SDL_Surface* text_surface = TTF_RenderText_Solid(t_font->get_font(), t_text.c_str(), t_font->get_color());
	if(t_font->get_font() != NULL){
		m_texture = SDL_CreateTextureFromSurface(t_renderer, text_surface);
		if(m_texture == NULL){
			printf("could not create texture from rendered text! error: %s\n", SDL_GetError());
		} else {
			m_width = text_surface->w;
			m_height = text_surface->h;
		}

		SDL_FreeSurface(text_surface);
	} else {
		printf("could not render text surface! error: %s\n", TTF_GetError());
	}

	return m_texture != NULL;
}

void Texture::set_color(Uint8 t_red, Uint8 t_green, Uint8 t_blue){
	SDL_SetTextureColorMod(m_texture, t_red, t_green, t_blue);
}

void Texture::set_blend_mode(SDL_BlendMode t_blending){
	SDL_SetTextureBlendMode(m_texture, t_blending);
}

void Texture::set_alpha(Uint8 t_alpha){
	SDL_SetTextureAlphaMod(m_texture, t_alpha);
}

void Texture::render(SDL_Renderer* t_renderer, int t_x, int t_y, SDL_Rect* t_clip, double t_angle, SDL_Point* t_center, SDL_RendererFlip t_flip){
	SDL_Rect render_quad = { t_x, t_y, m_width, m_height };

	if(t_clip != NULL){
		render_quad.w = t_clip->w;
		render_quad.h = t_clip->h;
	}

	SDL_RenderCopyEx(t_renderer, m_texture, t_clip, &render_quad, t_angle, t_center, t_flip);
}

int Texture::get_width(){
	return m_width;
}

int Texture::get_height(){
	return m_height;
}

std::string Texture::get_path(){
	return m_path;
}

void Texture::free(){
	if(m_texture != NULL){
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_path = "./res/textures/default.png";
		m_width = 0;
		m_height = 0;
	}
}

////////////////////////////////
