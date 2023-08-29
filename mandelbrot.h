#pragma once

#include "iostream"
#include "cmath"
#include "numeric"
#include "complex"
#include "SDL.h"

class mandelbrot {
public:
	mandelbrot();
	~mandelbrot();
	void display();
	int isInSet(std::complex<double>);
	void handleEvents();
private: 
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};
