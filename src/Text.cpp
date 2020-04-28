#include "../include/Text.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Text::Text(){
	m_text = "No Text";
	m_x = 0, m_y = 0;
	m_width = 0, m_height = 0;
	/*m_render_quad.x = m_x;        //TODO:implement render_quad later
	m_render_quad.y = m_y;
	m_render_quad.w = m_width;
	m_render_quad.h = m_height;*/
	m_angle = 0.0f;
	m_center = NULL;
	m_flip = SDL_FLIP_NONE;
}

Text::~Text(){
    free();
}

void Text::init(Font t_font, Texture t_texture){
	m_font = t_font;
	m_texture = t_texture;
}

void Text::change_font(Font t_font){
	m_font = t_font;
}

Font* Text::get_font(){
	return &m_font;
}

Texture* Text::get_texture(){
	return &m_texture;
}

void Text::reload(){
	m_texture.free();
}

void Text::set_position(int t_xpos, int t_ypos){
	m_x = t_xpos;
	m_y = t_ypos;
	/*renderQuad.x = x; //TODO:implement render_quad later
	renderQuad.y = y;*/
} 

int Text::get_x(){
	return m_x;
}

int Text::get_y(){
	return m_y;
}

int Text::get_width(){
	return m_width;
}

int Text::get_height(){
	return m_height;
}

/* //m_render_quad TODO
void Text::set_clip(SDL_Rect* t_clip){
	m_render_quad.w = t_clip->w;
	m_render_quad.h = t_clip->h;
} 

SDL_Rect Text::get_clip(){
	return m_render_quad;
}
*/

void Text::set_angle(double t_angle){
	m_angle = t_angle;
}

double Text::get_angle(){
	return m_angle;
}

void Text::set_center(SDL_Point* t_point){
	m_center = t_point;
}

SDL_Point* Text::get_center(){
	return m_center;
}

void Text::set_flip(SDL_RendererFlip t_flip){
	m_flip = t_flip;
}

SDL_RendererFlip Text::get_flip(){
	return m_flip;
}

void Text::set_text(std::string t_text){
	m_text = t_text;
}

std::string Text::get_text(){
	return m_text;
}

void Text::load_texture(SDL_Renderer* t_renderer){
	if(!m_texture.load_from_rendered_text(t_renderer, &m_font, m_text)){
		printf("failed to load from rendered text!\n");
	} else {
		m_width = m_texture.get_width();
		m_height = m_texture.get_height();
		/*renderQuad.w = w;
		renderQuad.h = h;*/
	}
}

//missing void set_and_load(...) because the definition has to be in the same file with the declaration
//shitty, i know

void Text::render(SDL_Renderer* t_renderer){ //TODO: work on the clip feature; it doesn't clip correctly; look at the NULL
	m_texture.render(t_renderer, m_x, m_y, NULL, m_angle, m_center, m_flip);
}

void Text::free(){
	m_text = "No Text";
	m_x = 0, m_y = 0;
	m_width = 0, m_height = 0;
	m_angle = 0.0f;
	m_center = NULL;
	m_flip = SDL_FLIP_NONE;
	m_font.free();
	m_texture.free();
}

////////////////////////////////
