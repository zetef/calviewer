#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#include "Text.h"
#include "Event.h"

class Date {
	public:
		////////////////////////////////
		/// Public Member Functions ////
		////////////////////////////////

		//default constructor
		Date(); 

		//sets all variables to a default value
		void init();

		//sets the date's day
		void set_day(int t_day);

		//returns the date's day
		int get_day();

		//sets the date month
		void set_month(int t_month);

		//returns date's month
		int get_month();

		//sets the date year
		void set_year(int t_year);

		//returns date's year
		int get_year();

		//sets the date's correspondness of the month (terrible description i know)
		void set_flag(bool t_set);

		//returns the date's correspondness of the month
		bool get_flag();

		//returns the text object
		//Text* get_text();
		
		//updates the event's variables
		void update_event();
		
		//defaults variables, frees the text and inits the event
		void free();

		////////////////////////////////

	private:
		////////////////////////////////
		///// Private Member Data //////
		////////////////////////////////

		//day   : ranges between 1 - 31
		//months: ranges between 0 - 11
		//years : since          1900

		bool 	m_this_month;             //records if the day corresponds to the month
		int 	m_day, m_month, m_year;   //date's values
		//Text 	m_text;                   //the text that shows the date
		Event 	m_event;                  //a date can have an event

		////////////////////////////////
};
