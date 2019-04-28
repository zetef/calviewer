#include "../include/utility.h"

void assign(std::string a[], std::string b[], int n){
    for(int i = 0; i < n; i++)
        a[i] = b[i];
}

void assign(int a[], int b[], int n){
    for(int i = 0; i < n; i++)
        a[i] = b[i];
}

void assign(SDL_Color a, SDL_Color b){
    a.r = b.r;
    a.g = b.g;
    a.b = b.b;
}

bool isNumber(const std::string& s){
    std::string::const_iterator it = s.begin();
    while(it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

float map(float value, float start1, float stop1, float start2, float stop2){
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius){
    const int32_t diameter = (radius * 2);
    
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);
    
    while(x >= y){
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX - y, centreY + x);
    
        if(error <= 0){
            ++y;
            error += ty;
            ty += 2;
        }
        
        if(error > 0){
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
