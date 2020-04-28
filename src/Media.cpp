#include "../include/Media.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Media::Media(){
	m_textures.clear();
	//m_fonts.clear();
}

Media::~Media(){
	free();
}

bool Media::load(SDL_Renderer* t_renderer){
	bool success = true;
	
	//reading from file the textures that need to load
	std::string path, key;
	Texture texture;
	std::ifstream tex("./io/textures.in");
	while(tex >> key >> path){
		if(!texture.load_from_file(t_renderer, path)){
			printf("failed to load image \"%s\"\n\n", texture.get_path().c_str());
			success = false;
		} else {
			m_textures[key] = texture;
		}
		texture.free();
	}
	
	/*
	Font font;
	std::ifstream txts("./io/fonts.in");
	while(txts >> key >> path){
		font.set_path(path);
		//font.load(); //just reading the font path, not interesed in loading it
		m_fonts[key] = font;
		//font.free(); //not necessary
	}
	*/
	
	return success;
}

void Media::render(SDL_Renderer* t_renderer, std::string t_name, int t_x, int t_y, SDL_Rect* t_clip, double t_angle, SDL_Point* t_center, SDL_RendererFlip t_flip){
	m_textures[t_name].render(t_renderer, t_x, t_y, t_clip, t_angle, t_center, t_flip);
}

std::map<std::string, Texture>* Media::get_textures(){
	return &m_textures;
}

/*std::map<std::string, Font>* Media::get_fonts(){
	return &m_fonts;
}*/

void Media::show_textures(){
	if(!m_textures.empty()){
		printf("in map textures:\n");
		std::map<std::string, Texture>::iterator it_texture;
		for(it_texture = m_textures.begin(); it_texture != m_textures.end(); it_texture++){
			printf("\t[%s] : path : \"%s\" | "
					"width : %d | "
					"height : %d\n", it_texture->first.c_str(), 
							it_texture->second.get_path().c_str(), 
							it_texture->second.get_width(), 
							it_texture->second.get_height());
		}
	}
}

/*void Media::show_fonts(){
	if(!m_fonts.empty()){
		printf("in map fonts:\n");
		std::map<std::string, Font>::iterator it_font;
		for(it_font = m_fonts.begin(); it_font != m_fonts.end(); it_font++){
			printf("\t[%s] : path : \"%s\" | "
					"size : %d | "
					"color : r: %d, g: %d, b: %d, a: %d\n", 
							it_font->first.c_str(), 
							it_font->second.get_path().c_str(), 
							it_font->second.get_size(), 
							it_font->second.get_color().r,
							it_font->second.get_color().g,
							it_font->second.get_color().b,
							it_font->second.get_color().a);
		}
	}
}*/

void Media::free(){
	std::map<std::string, Texture>::iterator it_texture;
	for(it_texture = m_textures.begin(); it_texture != m_textures.end(); it_texture++){
		it_texture->second.free();
	}
	
	/*std::map<std::string, Font>::iterator it_font;
	for(it_font = m_fonts.begin(); it_font != m_fonts.end(); it_font++){
		it_font->second.free();
	}*/
}

////////////////////////////////
