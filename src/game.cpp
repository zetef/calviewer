#include "../include/game.h"

game_t::game_t(std::string title){
    window = NULL;
    renderer = NULL;
    name = title;
}

game_t::~game_t(){
    free();
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
                }
                
                if(TTF_Init() == -1){
                    printf("could not initialize SDL_ttf! error: %s\n", TTF_GetError());
                    success = false;
                }
                
                state.init();
                    
			}
		}
	}

	return success;
}

void game_t::free(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    
    state.free();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
