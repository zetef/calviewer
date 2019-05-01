#include "../include/text.h"

text_t::text_t(){
    font.free();
    texture.free();
    name = " ";
    text = ".";
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

text_t::~text_t(){
    free();
}

void text_t::init(font_t f, texture_t t){
    font = f;
    texture = t;
    name = f.name;
    text = f.text;
}

void text_t::setPosition(int xf, int yf){
    x = xf;
    y = yf;
}

void text_t::setText(std::string text){
    font.text = text;
}

void text_t::loadTexture(SDL_Renderer* renderer){
    texture.loadFromRenderedText(renderer, font);
    w = texture.getWidth();
    h = texture.getHeight();
}

void text_t::render(SDL_Renderer* renderer){
    texture.render(renderer, x, y);
}

void text_t::free(){
    font.free();
    texture.free();
}
