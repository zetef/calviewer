#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../include/game.h"
#include "../include/timer.h"
#include "../include/media.h"

int main(int argc, char* argv[])
{

#if DEBUG
    freopen("./io/error.out", "w", stdout);
#endif

    game_t* game = new game_t("kalendar");
    media_t* media = new media_t();
    
    if(!game->init()){
        printf("failed to initialize %s. error: %s\n", game->name.c_str(), SDL_GetError());
    } else {
        if(!media->load(game->renderer)){
            printf("failed to load media. error: %s\n", SDL_GetError());
        } else {
            media->showTextures();
            
            SDL_Color color = {0x00, 0x00, 0x00, 0xff};
            timer_t fpsTimer;
            timer_t capTimer;
            std::stringstream timeText;
            unsigned int countedFrames = 0;
            fpsTimer.start();
            
            while(!game->state.quit){
                capTimer.start();
                
                //handle input
                game->state.handle();
                
                
                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if(avgFPS > 2000000){
                    avgFPS = 0;
                }
                timeText.str("");
                timeText << "average fps (with cap): " << avgFPS;
                if(!media->textures["FPSText"].loadFromRenderedText(timeText.str().c_str(), color, media->hbold, game->renderer)){
                    printf( "could not render fps texture!\n" );
                }
                
                //rest of the game
                SDL_SetRenderDrawColor(game->renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(game->renderer);
                
                //fps show
                media->render(game->renderer, "FPSText", (SCREEN_WIDTH - media->textures["FPSText"].getWidth()) / 2, (SCREEN_HEIGHT - media->textures["FPSText"].getHeight()) / 2);
                
                SDL_RenderPresent(game->renderer);
                
                ++countedFrames;
                int frameTicks = capTimer.getTicks();
                if(frameTicks < SCREEN_TICK_PER_FRAME){
                    SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
                }
            }
        }
    }
    
    delete game;
    return 0;
}
