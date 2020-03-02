#pragma once

#include <SDL.h>
#undef main
#include <iostream>
#include <algorithm>   
#include <cmath>
#include <windows.h>

using namespace std;
using std::string;

double multiplikator = 6;
const int SCREEN_WIDTH = 192 * multiplikator, SCREEN_HEIGHT = 108 * multiplikator;
bool quit = false, hidden = false;
Uint32* pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];


struct function
{
public:
	double at(double x) {
		return sin(x);
	}
	function() {}
};

double getSum(function f, double x1, double x2, int n, bool upper) {
	double sum = 0;
	double interval = abs(x2 - x1) / n;
	for (double x = x1; x < x2; x += interval)
		sum += abs(upper ? (max(f.at(x + interval), f.at(x))) : (min(f.at(x + interval), f.at(x)))) * interval;
	return sum;
}

void drawFunction(Uint32* pixels, function f, double x1, double x2, double y1, double y2, double grid_density) {
	double
		interval_x = abs(x2 - x1) / SCREEN_WIDTH,
		interval_y = abs(y2 - y1) / SCREEN_HEIGHT
	;
	for (int x = SCREEN_WIDTH / 2; x < SCREEN_WIDTH; x += (int)(1 / interval_x)) {
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			pixels[y * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 0 * 256 * 256 + 255 * 256 + 255);
		if (interval_x == 0)
			break;
	}
	for (int x = SCREEN_WIDTH / 2; x > 0; x -= (int)(1 / interval_x)) {
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			pixels[y * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 0 * 256 * 256 + 255 * 256 + 255);
		if (interval_x == 0)
			break;
	}

	for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y += (int)(1 / interval_y)) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			pixels[y * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 0 * 256 * 256 + 255 * 256 + 255);
		if (interval_y == 0)
			break;
	}
	for (int y = SCREEN_HEIGHT / 2; y > 0; y -= (int)(1 / interval_y)) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			pixels[y * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 0 * 256 * 256 + 255 * 256 + 255);
		if (interval_y == 0)
			break;
	}

	for (int x = 0; x < SCREEN_WIDTH; x++) {
		int y = (-f.at((x-SCREEN_WIDTH/2) * interval_x)) / interval_y +(SCREEN_HEIGHT/2);
		if (y >= 0 && y < SCREEN_HEIGHT)
			pixels[y * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 0 * 256 * 256 + 255 * 256 + 0);
	}

	for (int x = 0; x < SCREEN_WIDTH; x++)
		pixels[SCREEN_HEIGHT / 2 * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 255 * 256 * 256 + 255 * 256 + 255);
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		pixels[y * SCREEN_WIDTH + SCREEN_WIDTH / 2] = (255 * 256 * 256 * 256 + 255 * 256 * 256 + 255 * 256 + 255);
}
int main()
{
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	SDL_Window* window = SDL_CreateWindow("GrafikRechner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);


	function f;
	cout << getSum(f, 0, 4, 8, 1) << endl;
	int x2 = 10, y2 = 10;
	while (!quit)
	{
		//event handling
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case(SDL_WINDOWEVENT_MINIMIZED):
				hidden = true;
				break;
			case(SDL_WINDOWEVENT_RESTORED):
				hidden = false;
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				x2--;
				break;
			case SDLK_d:
				x2++;
				break;
			case SDLK_w:
				y2++;
				break;
			case SDLK_s:
				y2--;
			}
			break;
		}
		cout << -x2 << " " << x2 << " " << -y2 << " " << y2 << endl;
		memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		drawFunction(pixels, f, -x2, x2, -y2, y2 ,2);
		SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	return 0x1a4;
}