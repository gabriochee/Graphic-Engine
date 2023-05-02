#include "SDL.h"
#include "Geometry.h"
#include "Calculations.h"
#include <iostream>
#include <vector>
#undef main

using namespace std;

int main() {
	
	SDL_Init(SDL_INIT_VIDEO);

	SDL_DisplayMode DisplayMode;
	SDL_GetCurrentDisplayMode(0, &DisplayMode);

	int width = DisplayMode.w;
	int height = DisplayMode.h;

	int win_width = width * 1 / 2;
	int win_height = height * 1 / 2;

	SDL_Window* window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event e;
	
	Circle c(win_width / 2, win_height / 2, 50);
	Rectangle r(win_width / 3, win_height / 3, 100, 20);

	Shape t(win_width / 2, win_height / 2);
	
	t.addTriangle(getCircleRepresentation(&c, 20));

	setShapeColor(&t, { 255, 0, 0, 255 });

	drawShape(&t, renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(1000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}