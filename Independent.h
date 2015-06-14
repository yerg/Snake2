#ifndef INDEPENDENT_H
#define INDEPENDENT_H


#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <memory>
#include <string>
#include <deque>
#include <vector>
#include <functional>
#include <cstdlib>
#include <ctime>
#include "Enums.h"

typedef unsigned char byte;
using std::shared_ptr;
using std::make_shared;

struct Point{
	int x;
	int y;
	Point(){}
	Point(int x, int y) : x(x), y(y){}
	void Set(int x, int y){this->x=x;this->y=y;}
	bool operator==(const Point &rhs) const {return (this->x==rhs.x && this->y==rhs.y);}
	bool operator!=(const Point &rhs) const {return !(*this==rhs);}
};


#endif