#include "../include/utility.h"

void assign(std::string a[], std::string b[], int n) {
    for(int i = 0; i < n; i++)
        a[i] = b[i];
}

void assign(int a[], int b[], int n) {
    for(int i = 0; i < n; i++)
        a[i] = b[i];
}

void assign(SDL_Color a, SDL_Color b) {
    a.r = b.r;
    a.g = b.g;
    a.b = b.b;
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while(it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

float map(float value, float start1, float stop1, float start2, float stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

