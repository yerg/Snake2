#ifndef INDEPENDENTINCLUDE_H
#define INDEPENDENTINCLUDE_H


#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <memory>

typedef unsigned char byte;
using std::shared_ptr;
using std::make_shared;
struct Point{
	int x;
	int y;
	Point(){}
	Point(int x, int y) : x(x), y(y){}
};


#endif