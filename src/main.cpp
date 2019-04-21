#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "../include/game.h"

int main(int argc, char* argv[])
{
#if DEBUG
    freopen("error.out", "w", stdout);
#endif
    
    game_t* game = new game_t("kalendar");
    
    if(!game->init()){
        printf("failed to initialize %s. error: %s\n", game->getName().c_str(), SDL_GetError());
    } else {
        if(!game->loadMedia()){
            printf("failed to load media. error: %s\n", SDL_GetError());
        } else {
            while(!game->state.quit){
                game->state.handle();
                
                SDL_SetRenderDrawColor(game->getRenderer(), 0x00, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(game->getRenderer());
                
                game->render(game->getTexture(0), 0, 0, NULL);
                
                SDL_RenderPresent(game->getRenderer());
            }
        }
    }
    
    delete game;
    return 0;
}
