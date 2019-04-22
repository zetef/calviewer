#include "../include/game.h"

game_t::game_t(std::string title){
    printf("initializing %s...\n", title.c_str());
    window = NULL;
    renderer = NULL;
    name = title;
    printf("game initialized!\n\n");
}

game_t::~game_t(){
    printf("destructing game: %s...\n", name.c_str());
    free();
    printf("game destructed!\n\n");
}

std::string game_t::getName(){
    return name;
}

SDL_Renderer* game_t::getRenderer(){
    return renderer;
}

bool game_t::init(){
    bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("could not initialize sdl! rrror: %s\n", SDL_GetError());
		success = false;
	} else {
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("warning: Linear texture filtering not enabled!\n");
		}

		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL){
			printf("could not create window! error: %s\n", SDL_GetError());
			success = false;
		} else {
			renderer = SDL_CreateRenderer(window, DEFAULT_DRIVER, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL){
				printf("could not create renderer! error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if(!( IMG_Init(imgFlags) & imgFlags)){
					printf("could not initialize SDL_image! error: %s\n\n", IMG_GetError());
					success = false;
                } else {
                    state.init();
                    
                }
			}
		}
	}

	return success;
}

bool game_t::loadMedia(){
    bool success = true;

    texture_t* arrowButton = new texture_t();
    
	if(!arrowButton->loadFromFile("./res/arrowButton.png", renderer)){
        printf("failed to load image \"%s\"\n\n", arrowButton->getLocation().c_str());
        success = false;
    } else {
        addTexture(arrowButton);
    }
	
	return success;
}

void game_t::showTextures(){
    for(unsigned int i = 0; i < textures.size(); i++){
        printf("[%d]: \"%s\"\n", i, textures[i]->getLocation().c_str());
    }
    printf("\n");
}

texture_t* game_t::getTexture(texture_t* texture){
    unsigned int i = getThroughTexturesUntil(texture);
    return textures[i];
}

void game_t::addTexture(texture_t* texture){
    textures.push_back(texture);
    printf("added texture at location \"%s\" in textures vector", texture->getLocation().c_str());
}

void game_t::removeTexture(texture_t* texture){ 
    unsigned int i = getThroughTexturesUntil(texture);
    textures.erase(textures.begin() + i);
}

void game_t::render(texture_t* texture, int x, int y, SDL_Rect* clip){
    unsigned int i = getThroughTexturesUntil(texture);
    textures[i]->render(x, y, renderer, clip);
}

unsigned int game_t::getThroughTexturesUntil(texture_t* texture){ //TODO implement a map container
    std::string path = texture->getLocation();
    unsigned int i = 0;
    while(textures[i]->getLocation() != path){
        i++;
        if(i > textures.size()){
            printf("could not find texture at \"%s\" in textures vector\n\n", path.c_str());
            return -1;
        }
    }
    return i;
}

unsigned int game_t::getThroughTexturesUntil(std::string path){
    unsigned int i = 0;
    while(textures[i]->getLocation() != path){
        i++;
        if(i > textures.size()){
            printf("could not find texture at \"%s\" in textures vector\n\n", path.c_str());
            return -1;
        }
    }
    return i;
}

texture_t* game_t::getTexture(std::string path){
    return textures[getThroughTexturesUntil(path)];
}

void game_t::free(){
    //textures
    for(unsigned int i = 0; i < textures.size(); i++){
        delete textures[i];
        removeTexture(textures[i]);
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    
    state.~state_t();
    
    IMG_Quit();
    SDL_Quit();
}
