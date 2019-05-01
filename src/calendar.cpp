#include "../include/calendar.h"

calendar_t::calendar_t(int dd, int mm, int yy){
    d = dd, fd = dd;
    m = mm, fm = mm;
    y = yy, fy = yy;
    std::string days_temp[] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
    std::string months_temp[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
    int nrDayMonth_temp[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    assign(days, days_temp, 7);
    assign(months, months_temp, 12);
    assign(nrDayMonth, nrDayMonth_temp, 12);
    
    //clearing the 2D array
    clear();
    generate();
}   

void calendar_t::handleEvent(SDL_Event* event){
    if(event->key.type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_LEFT){
            if(m - 1 < 0){
                m = 11;
                y--;
            } else
                m--;
        } else if(event->key.keysym.sym == SDLK_RIGHT){
            if(m + 1 > 11){
                m = 0;
                y++;
            } else 
                m++;
        } else if(event->key.keysym.sym == SDLK_UP){
            y++;
        } else if(event->key.keysym.sym == SDLK_DOWN){
            y--;
        } else if(event->key.keysym.sym == SDLK_RETURN){
            d = fd;
            m = fm;
            y = fy;
        }
        generate();
    }
}

void calendar_t::showCalendar(){
    printf("%s %d\n", months[m].c_str(), y); //the current month followed by the current year
    for(int i = 0; i < COLS; i++) //printing all the days
        printf("%s ", days[i].c_str());
    printf("\n");
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++)
            if(month[i][j].d < 10) //one digit
                printf("%d   ", month[i][j].d); //three spaces
            else //two digits, and the max
                printf("%d  ", month[i][j].d); //two spaces
    
        printf("\n");
    }
}

void calendar_t::renderCalendar(SDL_Renderer* renderer, media_t* media){
    std::stringstream wDay, day;
    int offx = 40;
    int offy = 20;
    int x1 = offx;
    int x2 = SCREEN_WIDTH - offx;
    int y1 = SCREEN_HEIGHT / 8 + offy;
    int y2 = SCREEN_HEIGHT - offy;
    int k = 0; //week day counte
    int w = 0; //width of last day
    int h = 0;
    int midp[7];
    
    wDay.str("");
    wDay << days[6];
    std::string WeekDayTextName = media->texts["WeekDayText"].name;
    media->texts[WeekDayTextName].setText(wDay.str());
    media->texts[WeekDayTextName].loadTexture(renderer);
    w = media->texts[WeekDayTextName].w;
    h = media->texts[WeekDayTextName].h;
    
    //first render week days
    for(int i = x1; k < 7;){ // TODO make scalable font DONE!
        wDay.str("");
        wDay << days[k];
        media->texts[WeekDayTextName].setText(wDay.str());
        media->texts[WeekDayTextName].loadTexture(renderer);
        
        //scalable text relative to the width of the window
        i = map(k, 0, 6, x1, x2 - w);
        
        midp[k] = i + media->texts[WeekDayTextName].w / 2;
        media->texts[WeekDayTextName].setPosition(i, y1);
        
        media->texts[WeekDayTextName].render(renderer);
        k++;
    }
    
    y1 = y1 + h + offy;
    int m = 0;
    int n = y1 + h + offy;
    //rendering the month days
    for(int i = 0; i < 6; i++){
        m = x1;
        n = map(i, 0, 5, y1, y2 - h);
        for(int j = 0; j < 7; j++){
            day.str("");
            day << month[i][j].d;
            std::string s = "DayText";
            if(month[i][j].thisMonth) s += "Y";
            else                      s += "N";
            
            media->texts[s].setText(day.str());
            media->texts[s].loadTexture(renderer);
            
            m = midp[j] - media->texts[s].w / 2;
            
            month[i][j].x = m;
            month[i][j].y = n;
            month[i][j].w = media->texts[s].w;
            month[i][j].h = media->texts[s].h;
            media->texts[s].setPosition(m, n);
            media->texts[s].render(renderer);
        }
    }
}

void calendar_t::generate(){
    clear();
    int d_temp = getWeekDay(1, m, y); //first day of the month
    d_temp = reverseDay(d_temp);
    
    int nr = nrDayMonth[m];
    if(leapYear(y) && m == 1) //from 28 to 29
        nr++;
    
    int k = getFirstWeek(d_temp, m, y, month); //returns the last day of the first week of the month
    int l = 0; //counter for days after the current month
    for(int i = 1; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            if(k < nr){ //the month did not end
                k++;
                month[i][j].d = k;
                month[i][j].thisMonth = true;
            } else { //the month ended
                l++;
                month[i][j].d = l;
                month[i][j].thisMonth = false;
            }
}

void calendar_t::clear(){
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            month[i][j].d = 0;
}

int calendar_t::reverseDay(int a){
    unsigned int b = a;
    if(b == 0)
        b = 7;
    b--;
    return b;
}

int calendar_t::getWeekDay(int dd, int mm, int yy){
    std::tm time_in = {0, 0, 0, dd, mm, yy - 1900};
    std::time_t time_temp = std::mktime(&time_in);
    const std::tm* time_out = std::localtime(&time_temp);
    
    return time_out->tm_wday;
}

bool calendar_t::leapYear(int yy){
    if(yy % 4 == 0)
        if(yy % 100 == 0)
            if(yy % 400 == 0) return true;
            else return false;
        else return true;
    else return false;
}

int calendar_t::getFirstWeek(int st, int mnth, int yy, day_t month[6][7]){
    int mnth_temp = mnth;
    if(mnth_temp - 1 < 0)
        mnth_temp = 11;
    else
        mnth_temp--;
    
    int v = nrDayMonth[mnth_temp];
    if(leapYear(yy) && mnth_temp == 1) //from 28 to 29
        v++;
    
    int k = 0;
    for(int i = st - 1; i >= 0; i--){ //!!!if it is unsigned int it make overflow!!!
        month[0][i].d = v;
        month[0][i].thisMonth = false;
        v--;
    }
    
    for(int i = st; i < 7; i++){
        k++;
        month[0][i].d = k;
        month[0][i].thisMonth = true;
    }
    return k;
}
