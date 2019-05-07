#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <sstream>

#include "Event.h"
#include "Date.h"
#include "Media.h"
#include "constants.h"
#include "utility.h"

class Calendar{
	public:
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////

		//generates calendar from the current day/month/year
		Calendar(SDL_Renderer* t_renderer, int t_day, int t_month, int t_year);

		//destructor that frees all memory
		~Calendar();

		//handles events that change the data member
		void handle_event(SDL_Event* t_event);

		//generates a new calendar
		void generate();

		//prints to stdout the calendar
		void show_calendar();

		//renders the calendar to the screen
		void render_calendar(SDL_Renderer* t_renderer);
		
		//frees all memory used by font and texture
		void free();

		////////////////////////////////

	private:
		////////////////////////////////
		/// Private Member Functions ///
		////////////////////////////////

		//clears the calendar 2D array and sets all values to 0
		void clear();

		//substracts 1 from the current day; monday becomes sunday etc.
		void reverse_day(int* t_day);

		//substracts 1 from the current month; january becomes december etc.
		void reverse_month(int* t_month);

		//returns the name of that week day
		int get_week_day(int t_day, int t_month, int t_year);

		//checks if year is leap year
		bool leap_year(int t_year);

		//sets the boundary of a day's texture
		//void set_boundary(int t_x, int t_y, int t_width, int t_height);

		//the calendar's first row is filled with the first week of that month; 
		//returns the last day from that month
		int get_first_week(int t_start, int t_mnth, int t_year, Date t_month[ROWS][COLS]);

		//initializes all text parts 
		void init_text(SDL_Renderer* t_renderer);
		
		//initializes all weekdays
		void init_weekdays(std::map<std::string, Font> t_fonts);

		//reads holidays from file into the event array
		void read_holidays();

		////////////////////////////////
        
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////
		
		//day   : ranges between 1 - 31
		//months: ranges between 0 - 11
		//years : since          1900
		
		int                         m_initial_day, m_initial_month, m_initial_year; //initial day, month, year
		int                         m_current_day, m_current_month, m_current_year; //variable day, month, year
		std::string                 m_days[7];                                      //names of each day of a week
		std::string                 m_months[12];                                   //names of each month of a year
		int                         m_number_day_month[12];                         //number of days that each month has
		//Text                        m_weekdays[7];                                  //names of each weekday as text; more special because they never change
		Date                        m_month[ROWS][COLS];                            //the calendar itself tha holds all the days
		Event                       m_holidays[MAX_HOLIDAYS];                       //all the important holidays
		std::map<std::string, Text> m_texts;                                        //all the texts that i will be using in file texts.in
		
		///////////////////////////////
};
