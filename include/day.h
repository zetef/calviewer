#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#include "event.h"

class day_t{
    public:
        day_t();
        int d;
        int x, y;
        int w, h;
        //event_t event;
        bool hasEvent;
        bool thisMonth;
};
