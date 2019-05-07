#pragma once

#include <iostream>
#include <stdio.h>
#include <string>

class Event {
    public:
        ////////////////////////////////
        /// Public Member Functions ////
        ////////////////////////////////
        
        //default constructor
        Event();
        
        //sets all variables to a default value
        void init();
        
        //sets the event's title
        void set_title(std::string t_title);
        
        //sets the event's day
        void set_day(int t_day);
        
        //return the event's day
        int get_day();
        
        //sets the event's month
        void set_month(int t_month);

        //return the event's month
        int get_month();
        
        //sets the event's year
        void set_year(int t_year);
        
        //return the event's year
        int get_year();
        
         //checks whetever there is an event on this date
         //void check();
	
	//frees memory used by event
	void free();
        
        ////////////////////////////////
        
    private:
        
        ////////////////////////////////
        ///// Private Member Data //////
        ////////////////////////////////
        
        //day   : ranges between 1 - 31
        //months: ranges between 1 - 12
        //years : since          1900
        
        bool m_exist;                   //there is an event
        std::string m_title;            //the title of the event
        int m_day, m_month, m_year;             //the date of the event
        //more features to come

        ////////////////////////////////
};
