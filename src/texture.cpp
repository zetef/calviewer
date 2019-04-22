#include "../include/texture.h"

texture_t::texture_t(){
    printf("initializing texture from default location \"./res/default.png\"\n");
	mTexture = NULL;
    location = "./res/default.png";
	width = 0;
	height = 0;
    printf("texture initialized!\n\n");
}

texture_t::~texture_t(){
	printf("destructing texture from: %s\n", location.c_str());
    free();
    printf("texture destructed!\n\n");
}

bool texture_t::loadFromFile(std::string path, SDL_Renderer* renderer){
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
			printf("Unable to create texture from %s! SDL Error: %s\n\n", path.c_str(), SDL_GetError());
		} else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
    
}

void texture_t::free(){
    if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
	}
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

void texture_t::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip){
	SDL_Rect renderQuad = { x, y, width, height };

	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int texture_t::getWidth(){
    return width;
}

int texture_t::getHeight(){
    return height;
}

std::string texture_t::getLocation(){
    return location;
}
