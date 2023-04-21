#include "SDL.h"
#include "Geometry.h"
#include "Calculations.h"
#undef main
#include <iostream>

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

	Rectangle rect(win_width / 2, win_height / 2, 200, 50);

	int numkeys = 0;

	while (true)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_MOUSEMOTION) {
				rect.o.x = e.motion.x;
				rect.o.y = e.motion.y;
			}
			else if (e.type == SDL_MOUSEWHEEL) {
				const Uint8* kState = SDL_GetKeyboardState(&numkeys);
				if (e.wheel.y > 0) {
					rect.rotate(rect.rotation + degToRad(2));
				}
				else if (e.wheel.y < 0) {
					rect.rotate(rect.rotation - degToRad(2));
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		fillRectangle(&rect, renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}


	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}