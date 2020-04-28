#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

#include "Calendar.h"

class State{
	public:
		
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////
		
		//defaults variables
		State();
		
		//frees the memory
		~State();
		
		//initializes the state 
		void init();
		
		//handles the input
		void handle(Calendar* t_calendar);
		
		//returns the event it uses
		SDL_Event get_event();
		
		//returns the state's quit variable
		bool get_quit();
		
		//frees any memory
		void free();
		
		////////////////////////////////
		
	private:
		
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////
		
		SDL_Event m_event;
		bool 	  m_quit;
		
		////////////////////////////////
		
};
