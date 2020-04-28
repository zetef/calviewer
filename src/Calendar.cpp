#include "../include/Calendar.h"

////////////////////////////////
/// Public Member Functions ////
////////////////////////////////

Calendar::Calendar(SDL_Renderer* t_renderer, int t_day, int t_month, int t_year) {
	m_current_day   = t_day,    m_initial_day   = t_day;
	m_current_month = t_month,  m_initial_month = t_month;
	m_current_year  = t_year,   m_initial_year  = t_year;
	
	std::string days_temp[]             = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
	std::string months_temp[]           = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
	int         number_day_month_temp[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	assign(m_days, days_temp, 7); //7 days
	assign(m_months, months_temp, 12); //12 months
	assign(m_number_day_month, number_day_month_temp, 12); //12 months
	
	for(int i = 0; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			m_month[i][j].init();
		}
	}
	
	//////////////
	//Text stuff//
	//////////////
	
	//inits texts and reads values correspondingly
	init_text(t_renderer);
	
	//read all the important holidays from holidays.in
	read_holidays();
	
	//////////////
	
	///////////////////////////
	//2D Calendar Array stuff//
	///////////////////////////
	
	//generating the calendar
	generate();
	
	///////////////////////////
	
}

Calendar::~Calendar(){
	free();
}

void Calendar::handle_event(SDL_Event* t_event) {
	if(t_event->key.type == SDL_KEYDOWN) {
		if(t_event->key.keysym.sym == SDLK_LEFT) { //one month before
			if(m_current_month - 1 < 0){
				m_current_month = 11;
				--m_current_year;
			} else {
				--m_current_month;
			}
		} else if(t_event->key.keysym.sym == SDLK_RIGHT) { //one month afterwards
			if(m_current_month + 1 > 11) {
				m_current_month = 0;
				++m_current_year;
			} else {
				++m_current_month;
			}
		} else if(t_event->key.keysym.sym == SDLK_DOWN) { //one year before
			--m_current_year;
		} else if(t_event->key.keysym.sym == SDLK_UP) { //one year afterwards
			++m_current_year;
		} else if(t_event->key.keysym.sym == SDLK_RETURN) { //initial day/month/year
			m_current_day   = m_initial_day;
			m_current_month = m_initial_month;
			m_current_year  = m_initial_year;
		}
		
		//changes have been done so generate the new month
		generate();
	}
}

void Calendar::generate(){
	//makes sure to empty the calendar
	clear();
	
	int day_temp = get_week_day(1, m_current_month, m_current_year); //first day of the month
	reverse_day(&day_temp);
	
	int number = m_number_day_month[m_current_month];
	if(leap_year(m_current_year) && m_current_month == 1) //from 28 to 29; if the second month, february
		number++;
	
	int k = get_first_week(day_temp, m_current_month, m_current_year, m_month); //returns the last day of the first week of the month
	int l = 0; //counter for days after the current month
	for(int i = 1; i < ROWS; ++i) { //excluding the first week
		for(int j = 0; j < COLS; ++j) {
		if(k < number) { //the month did not end
			k++;
			m_month[i][j].set_day(k);
			m_month[i][j].set_flag(true);
		} else { //the month ended
			l++;
			m_month[i][j].set_day(l);
			m_month[i][j].set_flag(false);
		}
		}
	}
}

void Calendar::show_calendar() {
	printf("%s %d\n", m_months[m_current_month].c_str(), m_current_month); //the current month followed by the current year
	
	for(int i = 0; i < COLS; ++i) { //printing all the name of days
		printf("%s ", m_days[i].c_str());
	}
	printf("\n"); //one more space break
	
	for(int i = 0; i < ROWS; ++i) {
		for(int j = 0; j < COLS; ++j) {
		if(m_month[i][j].get_day() < 10) //one digit
			printf("%d   ", m_month[i][j].get_day()); //three spaces
		else //two digits, and the max
			printf("%d  " , m_month[i][j].get_day()); //two spaces
		}
		printf("\n");
	}
}

void Calendar::render_calendar(SDL_Renderer* t_renderer) {
	int offset			= 20;
	int offx                        = 40;                               //offset on the x axis
	int offy                        = 20;    			    //offset on the y axis
	int x_month 			= offset;
	int y_month 			= 10;
	int x_year			= m_texts["month"].get_width() + x_month + 5;
	int y_year			= y_month + m_texts["month"].get_height() - m_texts["year"].get_height();
	int x1                          = offx;
	int x2                          = SCREEN_WIDTH - offx;
	int y1                          = SCREEN_HEIGHT / 8 + offy;
	int y2                          = SCREEN_HEIGHT - offy;
	int k                           = 0;     			//week day counte
	m_texts["weekday"].set_and_load(t_renderer, m_days[6]);
	int width                       = m_texts["weekday"].get_width();    //width of last day
	int height                      = m_texts["weekday"].get_height();   //height of last dat
	int midpoints[COLS]             = {0};
	
	SDL_SetRenderDrawColor(t_renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderDrawLine(t_renderer, offset               , SCREEN_HEIGHT / 8, 
				       SCREEN_WIDTH - offset, SCREEN_HEIGHT / 8);
	
	//month and year text
	m_texts["month"].set_and_load(t_renderer, m_months[m_current_month]);
	m_texts["year"].set_and_load(t_renderer, m_current_year);
	
	m_texts["month"].set_position(x_month, y_month);
	m_texts["year"].set_position(x_year, y_year);
	
	m_texts["month"].render(t_renderer);
	m_texts["year"].render(t_renderer);
	
	
	//first render week days
	for(int i = x1; k < COLS; ++k){ // TODO make scalable font DONE!
		//scalable text relative to the width of the window
		i = map(k, 0, COLS - 1, x1, x2 - width);
		
		m_texts["weekday"].set_and_load(t_renderer, m_days[k]);
		midpoints[k] = i + m_texts["weekday"].get_width() / 2;
		m_texts["weekday"].set_position(i, y1);
		m_texts["weekday"].render(t_renderer);
	}
	
	//rendering the month days
	y1 = y1 + height + offy;
	int m = 0;
	int n = y1 + height + offy;
	
	for(int i = 0; i < ROWS; ++i){
		m = x1;
		n = map(i, 0, ROWS - 1, y1, y2 - height);
		for(int j = 0; j < COLS; j++){
			std::string s = "day_"; 
			if(m_month[i][j].get_flag()) s += "y"; //yes, this month
			else                       s += "n"; //no, not this month
			m_texts[s].set_and_load(t_renderer, m_month[i][j].get_day());
			m = midpoints[j] - m_texts[s].get_width() / 2; //aligning on the middle on the x axis
			m_texts[s].set_position(m, n);
			m_texts[s].render(t_renderer);
		}
	}
}

void Calendar::free(){
	m_initial_day = m_initial_month = m_initial_year = 0;
	m_current_day = m_current_month = m_current_year = 0;
	
	std::memset(m_days, 0, sizeof(m_days));
	std::memset(m_months, 0, sizeof(m_months));
	std::memset(m_number_day_month, 0, sizeof(m_number_day_month));
	
	/*
	m_mnth.free();
	m_year.free();
	
	for(int i = 0; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			m_month[i][j].free();
		}
	}*/
	
	for(std::map<std::string, Text>::iterator it = m_texts.begin(); it != m_texts.end(); ++it){
		it->second.free();
	}
	
	/*for(int i = 0; i < 7; i++){
		m_weekdays[i].free();
	}*/
	
	for(int i = 0; i < MAX_HOLIDAYS; i++){
		m_holidays[i].free();
	}
}

////////////////////////////////

////////////////////////////////
/// Private Member Functions ///
////////////////////////////////

void Calendar::clear() {
	for(int i = 0; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			m_month[i][j].init();
		}
		
	}
}

void Calendar::reverse_day(int* t_day) {
	if(*t_day == 0)
		*t_day = 7;
	--(*t_day);
}

void Calendar::reverse_month(int* t_month) {
	if(*t_month - 1 == -1)
		*t_month = 12;
	--(*t_month);
}

int Calendar::get_week_day(int t_day, int t_month, int t_year) {
	//0 seconds; 0 minutes; 0 hours; t_day day; t_month month; t_year year;
	std::tm time_in = {0, 0, 0, t_day, t_month, t_year - 1900};
	std::time_t time_temp = std::mktime(&time_in);
	const std::tm* time_out = std::localtime(&time_temp);
	return time_out->tm_wday;
}

bool Calendar::leap_year(int t_year) {
	if(t_year % 4 == 0)
		if(t_year % 100 == 0)
			if(t_year % 400 == 0) return true;
			else return false;
		else return true;
	else return false;
}

int Calendar::get_first_week(int t_start, int t_mnth, int t_year, Date t_month[ROWS][COLS]) {
	int prev_month = t_mnth;
	reverse_month(&prev_month);
	
	int v = m_number_day_month[prev_month];
	if(leap_year(t_year) && prev_month == 1) //from 28 to 29; if the second month, february
		++v;
	
	int k = 0;
	for(int i = t_start - 1; i >= 0; --i){ //!!!if it is unsigned int it makes overflow!!!
		t_month[0][i].set_day(v);
		t_month[0][i].set_flag(false);
		--v;
	}
	
	for(int i = t_start; i < 7; ++i){
		t_month[0][i].set_day(++k);
		t_month[0][i].set_flag(true);
	}
	
	return k;
}

void Calendar::init_text(SDL_Renderer* t_renderer){
	std::ifstream f("./io/texts.in");
	int size;
	int r, g, b, a;
	std::string name;
	std::string font_path;
	while(f >> name >> font_path >> size >> r >> g >> b >> a){
		SDL_Color color = {(Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a};
		m_texts[name].get_font()->init(font_path, size, color);
		m_texts[name].get_font()->load();
	}
	
	printf("in map texts:\n");
	for(std::map<std::string, Text>::iterator it = m_texts.begin(); it != m_texts.end(); ++it){
		printf("\t [%s] : path: %s\n", it->first.c_str(), it->second.get_font()->get_path().c_str());
	}
	
	//month and year text
	m_texts["month"].set_and_load(t_renderer, m_months[m_current_month]);
	m_texts["year"].set_and_load(t_renderer, m_current_year);
	
	//no need for weekday and month days yet
	
	//weekdays text
//  	for(int i = 0; i < 7; ++i){
// 		m_weekdays[i].get_font()->init(m_texts["weekday"].get_font()->get_path(),
// 					       m_texts["weekday"].get_font()->get_size(),
// 					       m_texts["weekday"].get_font()->get_color());
// 		m_weekdays[i].get_font()->load();
//  		m_weekdays[i].set_and_load(t_renderer, m_days[i]);
//  	}
}

void Calendar::read_holidays() {
	std::ifstream f("./io/holidays.in");
	std::string title;
	int day, month;
	int i = 0;
	while(!f.eof() && i < MAX_HOLIDAYS) {
		getline(f, title, ':');
		m_holidays[i].set_title(title);
		f >> day >> month;
		m_holidays[i].set_day(day);
		m_holidays[i].set_month(month);
		m_holidays[i].set_year(0); //every year these holidays happen
		++i;
	}
}

////////////////////////////////
