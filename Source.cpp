#pragma once

#include <SDL.h>
#undef main
#include <iostream>
#include <algorithm>   
#include <cmath>
#include <windows.h>
#include "vectors.h"

using namespace std;
using std::string;

double multiplikator = 6;
const int SCREEN_WIDTH = 192 * multiplikator, SCREEN_HEIGHT = 108 * multiplikator;
bool quit = false, hidden = false;
Uint32* pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];


struct function
{
public:
	double penis(double x) {
		return abs(sin(x)) +5.0 * exp(-pow(x, 100.0)) * cos(x);
	}
	double at(double x) {
		return sin(x);
	}
	function() {}
};

/*
	draws a line between two vec2 objects p1 and p2 onto a given pixel array pixels and returs a pointer to that very array
	size_x is the width of the frame (pixel array)
	size_y is the height of the frame (pixel array)
*/
void drawLine(Uint8* color, Uint32* pixels, vec2 p1, vec2 p2) {
	int y, x;
	float k = (p1.getY() - p2.getY()) / (p1.getX() - p2.getX());
	Uint32 color_int = color[0] * 256 * 256 * 256 + color[1] * 256 * 256 + color[2] * 256 + color[3];
	if (abs(p1.getX() - p2.getX()) > abs(p1.getY() - p2.getY()))
	{
		if (p1.getX() < p2.getX())
			swap(p1, p2);
		if (p2.getX() < 0)
			p2.setX(0);
		for (int x = p2.getX(); x < SCREEN_WIDTH && x <= p1.getX(); x++)
		{
			y = k * (x - p1.getX()) + p1.getY();
			if (y >= 0 && y < SCREEN_HEIGHT)
				pixels[y * SCREEN_WIDTH + x] = color_int;
		}
	}
	else
	{
		if (p1.getY() < p2.getY())
			swap(p1, p2);
		if (p2.getY() < 0)
			p2.setY(0);
		for (int y = p2.getY(); y < SCREEN_HEIGHT && y <= p1.getY(); y++)
		{
			x = (y - p1.getY()) / k + p1.getX();
			if (x >= 0 && x < SCREEN_WIDTH)
				pixels[y * SCREEN_WIDTH + x] = color_int;
		}
	}
}

double getSum(function f, double x1, double x2, int n, bool upper) {
	double sum = 0;
	double interval = abs(x2 - x1) / n;
	for (double x = x1; x < x2; x += interval)
		sum += abs(upper ? (max(f.at(x + interval), f.at(x))) : (min(f.at(x + interval), f.at(x)))) * interval;
	return sum;
}

void drawGrid(Uint32* pixels, double x1, double x2, double y1, double y2, double grid_density) {
	double
		interval_x = abs(x2 - x1) / SCREEN_WIDTH,
		interval_y = abs(y2 - y1) / SCREEN_HEIGHT
	;
	int color= (100 * 256 * 256 * 256 + 0 * 256 * 256 + 100 * 256 + 100);
	for (int x = SCREEN_WIDTH / 2; x < SCREEN_WIDTH; x += (int)(grid_density / interval_x)) {
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			pixels[y * SCREEN_WIDTH + x] = color;
		if (interval_x == 0)
			break;
	}
	for (int x = SCREEN_WIDTH / 2; x > 0; x -= (int)(grid_density / interval_x)) {
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			pixels[y * SCREEN_WIDTH + x] = color;
		if (interval_x == 0)
			break;
	}

	for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y += (int)(grid_density / interval_y)) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			pixels[y * SCREEN_WIDTH + x] = color;
		if (interval_y == 0)
			break;
	}
	for (int y = SCREEN_HEIGHT / 2; y > 0; y -= (int)(grid_density / interval_y)) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			pixels[y * SCREEN_WIDTH + x] = color;
		if (interval_y == 0)
			break;
	}

	for (int x = 0; x < SCREEN_WIDTH; x++)
		pixels[SCREEN_HEIGHT / 2 * SCREEN_WIDTH + x] = (255 * 256 * 256 * 256 + 255 * 256 * 256 + 255 * 256 + 255);
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		pixels[y * SCREEN_WIDTH + SCREEN_WIDTH / 2] = (255 * 256 * 256 * 256 + 255 * 256 * 256 + 255 * 256 + 255);
}

void drawFunction(Uint32* pixels, function f, double x1, double x2, double y1, double y2) {
	double
		interval_x = abs(x2 - x1) / SCREEN_WIDTH,
		interval_y = abs(y2 - y1) / SCREEN_HEIGHT
	;
	for (int x = 0; x < SCREEN_WIDTH-1; x++) {
		int ya = (-f.at((x - SCREEN_WIDTH / 2) * interval_x)) / interval_y +(SCREEN_HEIGHT / 2);
		int yb = (-f.at((x+1 - SCREEN_WIDTH / 2) * interval_x)) / interval_y + (SCREEN_HEIGHT / 2);
		Uint8 color[] = {255,0,255,0};
		drawLine(color, pixels, vec2(x,ya), vec2(x+1,yb));
	}
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
		drawGrid(pixels, -x2, x2, -y2, y2 , 3.141);
		drawFunction(pixels, f, -x2, x2, -y2, y2);
		SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	return 0x1a4;
}