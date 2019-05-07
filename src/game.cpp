#include "../include/Game.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Game::Game(std::string t_title){
    m_window = NULL;
    m_renderer = NULL;
    m_title = t_title;
}

Game::~Game(){
    free();
}

bool Game::init(){
    bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("could not initialize sdl! error: %s\n", SDL_GetError());
		success = false;
	} else {
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("warning: Linear texture filtering not enabled!\n");
		}

		m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							   SCREEN_WIDTH		  , SCREEN_HEIGHT          , SDL_WINDOW_SHOWN        );
		if(m_window == NULL){
			printf("could not create window! error: %s\n", SDL_GetError());
			success = false;
		} else {
			m_renderer = SDL_CreateRenderer(m_window, DEFAULT_DRIVER, SDL_RENDERER_ACCELERATED);
			if(m_renderer == NULL){
				printf("could not create renderer! error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int img_flags = IMG_INIT_PNG;
				if(!( IMG_Init(img_flags) & img_flags)){
					printf("could not initialize SDL_image! error: %s\n\n", IMG_GetError());
					success = false;
                
				}
			}
		}
                
                if(TTF_Init() == -1){
                    printf("could not initialize SDL_ttf! error: %s\n", TTF_GetError());
                    success = false;
                }
                
                m_state.init();
                
                SDL_Surface *icon;
                icon = SDL_LoadBMP("./res/icon.bmp");
                SDL_SetWindowIcon(m_window, icon);

                SDL_FreeSurface(icon);
	}

	return success;
}

SDL_Renderer* Game::get_renderer(){
	return m_renderer;
}

State* Game::get_state(){
	return &m_state;
}

std::string Game::get_title(){
	return m_title;
}

void Game::free(){
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    m_window = NULL;
    m_renderer = NULL;
    
    m_state.free();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

////////////////////////////////
