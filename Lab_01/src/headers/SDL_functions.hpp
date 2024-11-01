#pragma once

#include <iostream>
#include <SDL2/SDL.h>

bool init(SDL_Window** window, SDL_Renderer** renderer, int windowWidth, int windowLength);
void close(SDL_Window* window, SDL_Renderer* renderer);