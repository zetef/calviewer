#include "../include/texture.h"

texture_t::texture_t(){
	mTexture = NULL;
    location = "./";
	width = 0;
	height = 0;
}

texture_t::~texture_t(){
    free();
}

bool texture_t::loadFromFile(SDL_Renderer* renderer, std::string path){
	free();
    location = path;

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xff, 0x00));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
    
}

bool texture_t::loadFromRenderedText(SDL_Renderer* renderer, font_t fnt){
    free();
    
    fnt.load();
    
	SDL_Surface* textSurface = TTF_RenderText_Solid(fnt.font, fnt.text.c_str(), fnt.color);
	if(fnt.font != NULL){
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(mTexture == NULL){
			printf("could not create texture from rendered text! error: %s\n", SDL_GetError());
		} else {
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	} else {
		printf("could not render text surface! error: %s\n", TTF_GetError());
	}

	return mTexture != NULL;
}

void texture_t::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void texture_t::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(mTexture, blending);
}
		
void texture_t::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void texture_t::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_Rect renderQuad = { x, y, width, height };

	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int texture_t::getWidth(){
    return width;
}

int texture_t::getHeight(){
    return height;
}

void texture_t::setLocation(std::string path){
    location = path;
}

std::string texture_t::getLocation(){
    return location;
}

void texture_t::free(){
    if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
	}
}
