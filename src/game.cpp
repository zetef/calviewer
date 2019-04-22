#include "../include/game.h"

game_t::game_t(std::string title){
    window = NULL;
    renderer = NULL;
    font = NULL;
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

bool game_t::loadMedia(){
    bool success = true;
    
    //reading from file the textures that need to load
    std::string location, key;
    texture_t ex;
    std::ifstream f("./textures.in");
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
    
    font = TTF_OpenFont("./res/lazy.ttf", 28);
    if(font == NULL){
        printf("failed to load font from file \"%s\". error: %s\n", "./res/lazy.ttf", TTF_GetError());
        success = false;
    }
	
	return success;
}

void game_t::render(texture_t texture, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    textures[texture.getLocation()].render(renderer, x, y, clip, angle, center, flip);
}

void game_t::showTextures(){
    printf("in map textures:\n");
    std::map<std::string, texture_t>::iterator it;
    for(it = textures.begin(); it != textures.end(); it++){
        printf("\t[%s] : location : \"%s\" | "
                        "width : %d | "
                        "height : %d\n", it->first.c_str(), it->second.getLocation().c_str(), it->second.getWidth(), it->second.getHeight());
    }
}

texture_t game_t::getTexture(std::string path){
    return textures[path];
}

texture_t game_t::getTexture(texture_t texture){
    return textures[texture.getLocation()];
}

void game_t::addTexture(texture_t texture){
    textures.insert(std::pair<std::string, texture_t>(texture.getLocation(), texture));
    printf("added texture at location \"%s\" in textures vector\n", texture.getLocation().c_str());
}

void game_t::removeTexture(texture_t texture){ 
    textures.erase(texture.getLocation());
}

void game_t::free(){
    //textures
    std::map<std::string, texture_t>::iterator it;
    for(it = textures.begin(); it != textures.end(); it++){
        it->second.free();
    }
    
    TTF_CloseFont(font);
    font = NULL;
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    
    state.free();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
