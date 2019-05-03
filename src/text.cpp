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
    renderQuad.x = x;
    renderQuad.y = y;
    renderQuad.w = w;
    renderQuad.h = h;
    angle = 0.0f;
    center = NULL;
    flip = SDL_FLIP_NONE;
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

void text_t::setPosition(int xpos, int ypos){
    x = xpos;
    y = ypos;
    renderQuad.x = x;
    renderQuad.y = y;
} 

void text_t::setClip(SDL_Rect* clip){
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
} 

void text_t::setAngle(double a){
    angle = a;
}

void text_t::setCenter(SDL_Point* point){
    center = point;
}

void text_t::setFlip(SDL_RendererFlip f){
    flip = f;
}

void text_t::setText(std::string text){
    font.text = text;
}

void text_t::loadTexture(SDL_Renderer* renderer){
    if(!texture.loadFromRenderedText(renderer, font)){
        printf("failed to load from rendered text!\n");
    } else {
        w = texture.getWidth();
        h = texture.getHeight();
        renderQuad.w = w;
        renderQuad.h = h;
    }
}

void text_t::render(SDL_Renderer* renderer){ //TODO: work on the clip feature; it doesn't clip correctly; look at the NULL
    texture.render(renderer, x, y, NULL, angle, center, flip);
}

void text_t::free(){
    font.free();
    texture.free();
}
