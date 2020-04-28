#pragma once

#include <SDL2/SDL.h>
#include <cstdlib>
#include <string>

void assign(std::string a[], std::string b[], int n); //TODO use template. not used yet because errors
void assign(int a[], int b[], int n);
void assign(SDL_Color a, SDL_Color b);
bool is_number(const std::string& s);
float map(float value, float start1, float stop1, float start2, float stop2);
