#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include "../include/game.h"
#include "../include/timer.h"
#include "../include/media.h"
#include "../include/calendar.h"

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
            
            timer_t fpsTimer;
            timer_t capTimer;
            std::stringstream month;
            std::stringstream year;
            
            //get date and time
            std::time_t t = std::time(0);
            std::tm* now = std::localtime(&t);
            calendar_t* calendar = new calendar_t(now->tm_mday, now->tm_mon, now->tm_year + 1900);
            calendar->showCalendar();
            
            unsigned int countedFrames = 0;
            fpsTimer.start();
            
            while(!game->state.quit){
                capTimer.start();
                
                //handle input
                game->state.handle(calendar); //generating the new month only when new input is detected
                
                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if(avgFPS > 2000000)
                    avgFPS = 0;
                
                unsigned int offset = 20;
                int x = 20;
                int y = 10;
                unsigned int x1 = media->textures["MonthText"].getWidth() + x;
                unsigned int y1 = y;
                
                month.str("");
                year.str("");
                month << calendar->months[calendar->m];
                year << calendar->y;
            
                media->fonts["MonthText"].text = month.str();
                media->textures["MonthText"].loadFromRenderedText(game->renderer, media->fonts["MonthText"]);
            
                media->fonts["YearText"].text = year.str();
                media->textures["YearText"].loadFromRenderedText(game->renderer, media->fonts["YearText"]);
                
                //rendering
                SDL_SetRenderDrawColor(game->renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(game->renderer);
                
                SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xff);
                SDL_RenderDrawLine(game->renderer, offset, SCREEN_HEIGHT / 8, SCREEN_WIDTH - offset, SCREEN_HEIGHT / 8);
                
                media->render(game->renderer, "MonthText", x, y);
                media->render(game->renderer, "YearText", x1, y1);
                
                calendar->renderCalendar(game->renderer, media);
                
                SDL_RenderPresent(game->renderer);
                
                ++countedFrames;
                int frameTicks = capTimer.getTicks();
                if(frameTicks < SCREEN_TICK_PER_FRAME)
                    SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
            }
        }
    }
    
    delete game;
    return 0;
}
