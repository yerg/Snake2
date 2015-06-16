#ifndef DRAWER_H
#define DRAWER_H

#include "Independent.h"
#include "Graphics.h"

class Drawer {
	Graphics * graphics;
	int w, h;
	Image * map, *penalty, *lenght, *win1, *win2, *draw, *finish;
	bool initialized;

public:
	Drawer(Graphics *graphics);
	void Set(int w, int h, int penalty, int lenght);
	void Draw(std::vector<Section> letter);
};

#endif