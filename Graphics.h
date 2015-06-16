#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Independent.h"
#include "Image.h"

class Image;

class Graphics
{
private:
	SDL_Renderer* renderer;
	SDL_Window* mainWindow;
	TTF_Font* font;
public:
	Graphics(int width, int height, const char *title);
	~Graphics();
	Image* NewImage(char* file, int r=-1, int g=-1, int b=-1);
	Image* NewImage(std::wstring &text, SDL_Color &color, bool fast=false);
	void DestroyImage(Image* image);
	bool DrawImage(Image* img, int x, int y);
	bool DrawImage(Image* img, int x, int y, int startX, int startY, int srcW, int srcH, int w, int h);
	bool DrawImage(Image* img, int x, int y, int startX, int startY, int srcW, int srcH, double scale=1.0);
	void SetResolution(int w, int h);
	void Flip();
};

#endif