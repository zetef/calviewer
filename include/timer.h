#pragma once

#include <SDL.h>

class Timer{
	public:
		
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////
		
		//defaults variables
		Timer();

		//starts timer
		void start();
		
		//stops timer
		void stop();
		
		//pauses timer
		void pause();
		
		//upauses timer
		void unpause();

		//gets ticks
		Uint32 get_ticks();

		//checks if started
		bool is_started();
		
		//check if paused
		bool is_paused();
		
		////////////////////////////////

	private:
		
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////
		
		Uint32 m_start_ticks;  //started ticks
		Uint32 m_paused_ticks; //paused ticks
		bool   m_paused;       //is the timer paused
		bool   m_started;      //is the timer started
		
		////////////////////////////////

};
