#pragma once

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

#include "day.h"
#include "media.h"
#include "constants.h"
#include "utility.h"

class calendar_t{
    public:
        calendar_t(int dd, int mm, int yy);
        void handleEvent(SDL_Event* event);
        void generate();
        void showCalendar();
        void renderCalendar(SDL_Renderer* renderer, media_t* media);
        
        int d, m, y;
        std::string days[7];
        std::string months[12];
        int nrDayMonth[12];
        day_t month[ROWS][COLS];
    private:
        void clear();
        int reverseDay(int a);
        int getWeekDay(int dd, int mm, int yy);
        bool leapYear(int yy);
        int getFirstWeek(int st, int mnth, int yy, day_t month[ROWS][COLS]);
};
