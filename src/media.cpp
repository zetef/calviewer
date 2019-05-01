#include "../include/media.h"

media_t::media_t(){
    textures.clear();
    fonts.clear();
}

media_t::~media_t(){
    free();
}

bool media_t::load(SDL_Renderer* renderer){
    bool success = true;
    
    //reading from file the textures that need to load
    std::string location, key;
    texture_t texture;
    std::ifstream tex("./io/textures.in");
    while(tex >> location >> key){
        if(!texture.loadFromFile(renderer, location)){
            printf("failed to load image \"%s\"\n\n", texture.getLocation().c_str());
            success = false;
        } else {
            textures[key] = texture;
        }
        texture.free();
    }
    
    text_t text;
    font_t fnt;
    int size;
    int r, g, b, a;
    std::string path;
    std::ifstream txts("./io/texts.in");
    while(txts >> key >> size >> path >> r >> g >> b >> a){
        SDL_Color color = {(Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a};
        fnt.init(path, size, color);
        fnt.name = key;
        text.init(fnt, texture);
        /*textures[key] = texture;
        fonts[key] = fnt;*/
        texts[key] = text;
        texture.free();
        fnt.free();
        text.free();
    }
    
	return success;
}

void media_t::render(SDL_Renderer* renderer, std::string name, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    textures[name].render(renderer, x, y, clip, angle, center, flip);
}

void media_t::showTextures(){
    if(!textures.empty()){
        printf("in map textures:\n");
        std::map<std::string, texture_t>::iterator it;
        for(it = textures.begin(); it != textures.end(); it++){
            printf("\t[%s] : location : \"%s\" | "
                            "width : %d | "
                            "height : %d\n", it->first.c_str(), it->second.getLocation().c_str(), it->second.getWidth(), it->second.getHeight());
        }
    }
}

void media_t::free(){
    std::map<std::string, texture_t>::iterator itt;
    for(itt = textures.begin(); itt != textures.end(); itt++){
        itt->second.free();
    }
    
    std::map<std::string, font_t>::iterator itf;
    for(itf = fonts.begin(); itf != fonts.end(); itf++){
        itf->second.free();
    }
}
