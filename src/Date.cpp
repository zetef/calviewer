#include "../include/Date.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Date::Date() {
	init();
}

void Date::init(){
	m_day = 0;
	m_month = 0;
	m_year = 0;
	m_this_month = false;

	m_event.init();
}

void Date::set_day(int t_day) {
	m_day = t_day;
}

int Date::get_day() {
	return m_day;
}

void Date::set_month(int t_month) {
	m_month = t_month;
}

int Date::get_month() {
	return m_month;
}

void Date::set_year(int t_year) {
	m_year = t_year;
}

int Date::get_year() {
	return m_year;
}

void Date::set_flag(bool t_set) {
	m_this_month = t_set;
}

bool Date::get_flag() {
	return m_this_month;
}

// Text* Date::get_text() {
// 	return &m_text;
// }

void Date::update_event() {
	m_event.set_day(m_day);
	m_event.set_month(m_month);
	m_event.set_year(m_year);
	
	//m_event.check();
}

void Date::free() {
	init();
	//m_text.free();
}

////////////////////////////////
