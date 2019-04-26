#include "../include/font.h"

font_t::font_t(){
    font = NULL;
    path = "./";
    size = 10;
    text = ".";
    SDL_Color color_temp = {0x00, 0x00, 0x00, 0xff};
    assign(color, color_temp);
}

font_t::~font_t(){
    free();
}

void font_t::init(std::string p, int s, SDL_Color c){
    path = p;
    size = s;
    color = c;
}

bool font_t::load(){
    bool success = true;
    
    std::string s = "./res/" + path;
    font = TTF_OpenFont(s.c_str(), size);
    if(font == NULL){
        printf("failed to load font from file \"%s\". error: %s\n", s.c_str(), TTF_GetError());
        success = false;
    }
    
    return success;
}

void font_t::free(){
    TTF_CloseFont(font);
    font = NULL;
}
