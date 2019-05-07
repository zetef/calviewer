#include "../include/Event.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Event::Event() {
	init();
}

void Event::init(){
	m_exist = false;
	m_title = "No Event";
	
	m_day = 1;
	m_month = 1;
	m_year = 1900;
}

void Event::set_title(std::string t_title) {
	m_title = t_title;
}

void Event::set_day(int t_day) {
	m_day = t_day;
}

int Event::get_day(){
	return m_day;
}

void Event::set_month(int t_month) {
	m_month = t_month;
}

int Event::get_month(){
	return m_month;
}

void Event::set_year(int t_year) {
	m_year = t_year;
}

int Event::get_year(){
	return m_year;
}

// void Event::check() {
// 	if(){
// 		set_title();
// 	}
// }

void Event::free(){
	init();
}

////////////////////////////////
