#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include "../include/Game.h"
#include "../include/Timer.h"
#include "../include/Media.h"
#include "../include/Calendar.h"

int main(int argc, char* argv[])
{

	
	
#if DEBUG
	freopen("./io/error.out", "w", stdout);
#endif

	Game* game = new Game("calviewer");
	Media* media = new Media();
	
	if(!game->init()){
		printf("failed to initialize %s. error: %s\n", game->get_title().c_str(), SDL_GetError());
	} else {
		if(!media->load(game->get_renderer())){
			printf("failed to load media. error: %s\n", SDL_GetError());
		} else {
			media->show_textures();
 			//media->show_fonts();
			
			Timer fps_timer;
			Timer cap_timer;
			
			unsigned int counted_frames = 0;
			fps_timer.start();
			
			//get date and time
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);
			Calendar* calendar = new Calendar(game->get_renderer(), now->tm_mday, now->tm_mon, now->tm_year + 1900);
			calendar->show_calendar();
			
			while(!game->get_state()->get_quit()){
				cap_timer.start();
				
				//handle input
				game->get_state()->handle(calendar); //generating the new month only when new input is detected
				
				float avg_FPS = counted_frames / (fps_timer.get_ticks() / 1000.f);
				if(avg_FPS > 2000000)
				avg_FPS = 0;
				
				//rendering
				SDL_SetRenderDrawColor(game->get_renderer(), 0xff, 0xff, 0xff, 0xff);
				SDL_RenderClear(game->get_renderer());
				calendar->render_calendar(game->get_renderer());
				SDL_RenderPresent(game->get_renderer());
				
				++counted_frames;
				int frame_ticks = cap_timer.get_ticks();
				if(frame_ticks < SCREEN_TICK_PER_FRAME)
				SDL_Delay(SCREEN_TICK_PER_FRAME - frame_ticks);
			}
		}
	}
	
	delete game;
	return 0;
}
