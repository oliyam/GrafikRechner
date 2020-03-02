#pragma once

#include <SDL.h>
#undef main
#include <iostream>
#include <algorithm>   
#include <cmath>
#include <windows.h>

using namespace std;
using std::string;

struct function
{
public:
	double at(double x) {
		return 10.0 / (1.0 + x);
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

void drawFunctionCmd(function f, double x1, double x2) {
	HWND cmd = GetConsoleWindow();
	HDC dc = GetDC(cmd);
	COLORREF
		color1 = RGB(255, 255, 255),
		color2 = RGB(0, 255, 0)
		;
	int size_x = 500, size_y = 500;
	double interval = abs(x2 - x1) / size_x;
	for (int x = 0; x < size_x; x++)
		SetPixel(dc, x, -f.at(x * interval) + 500, color2);
	ReleaseDC(cmd, dc);
}

int main()
{
	function f;
	cout << getSum(f, 0, 4, 8, 1) << endl;
	while (1)
	{
		drawFunctionCmd(f, 0, 20);
	}
	return 0x1a4;
}