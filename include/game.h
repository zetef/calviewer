#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "constants.h"
#include "State.h"

class Game{
	public:
		
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////
		
		//creates a game with t_title
		Game(std::string t_title);
		
		//destroies the game objects
		~Game();

		//initializes the game
		bool init();
		
		//returns the renderer of the game
		SDL_Renderer* get_renderer();
		
		//returns the stae of the game
		State* get_state();
		
		//returns the game's title
		std::string get_title();

		//frees the memory allocated by the game
		void free();
		
		////////////////////////////////
		
	private:
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////
		
		std::string   m_title;
		SDL_Window*   m_window;
		SDL_Renderer* m_renderer;
		State         m_state;
		
		////////////////////////////////
		
};
