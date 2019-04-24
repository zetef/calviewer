#include "../include/media.h"

media_t::media_t(){
    textures.clear();
    hbold = NULL;
    hlight = NULL;
}

media_t::~media_t(){
    free();
}

bool media_t::load(SDL_Renderer* renderer){
    bool success = true;
    
    //reading from file the textures that need to load
    std::string location, key;
    texture_t ex;
    std::ifstream f("./io/textures.in");
    while(f >> location >> key){
        if(location != key){
            if(!ex.loadFromFile(renderer, location)){
                printf("failed to load image \"%s\"\n\n", ex.getLocation().c_str());
                success = false;
            }
        }
        textures[key] = ex;
        if(location == key) textures[key].setLocation(key);
        ex.free();
    }
    
    //font
    hbold = TTF_OpenFont("./res/helvetica-bold.ttf", 30);
    if(hbold == NULL){
        printf("failed to load font from file \"%s\". error: %s\n", "./res/helvetica-bold.ttf", TTF_GetError());
        success = false;
    }
    hlight = TTF_OpenFont("./res/helvetica-light.ttf", 30);
	if(hlight == NULL){
        printf("failed to load font from file \"%s\". error: %s\n", "./res/helvetica-light.ttf", TTF_GetError());
        success = false;
    }
    
	return success;
}

void media_t::render(SDL_Renderer* renderer, std::string name, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    textures[name].render(renderer, x, y, clip, angle, center, flip);
}

void media_t::showTextures(){
    printf("in map textures:\n");
    std::map<std::string, texture_t>::iterator it;
    for(it = textures.begin(); it != textures.end(); it++){
        printf("\t[%s] : location : \"%s\" | "
                        "width : %d | "
                        "height : %d\n", it->first.c_str(), it->second.getLocation().c_str(), it->second.getWidth(), it->second.getHeight());
    }
}

void media_t::free(){
    std::map<std::string, texture_t>::iterator it;
    for(it = textures.begin(); it != textures.end(); it++){
        it->second.free();
    }
    
    TTF_CloseFont(hbold);
    TTF_CloseFont(hlight);
    hbold = NULL;
    hbold = NULL;
}
