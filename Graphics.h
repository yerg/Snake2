#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "IndependentInclude.h"
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
	Image* NewImage(char* file);
	Image* NewImage(char* file, int r, int g, int b);
	Image* NewImage(std::wstring text, SDL_Color color);
	bool DrawImage(Image* img, int x, int y);
	bool DrawImage(Image* img, int x, int y, int startX, int startY, int srcW, int srcH, int w, int h);
	bool DrawImage(Image* img, int x, int y, int startX, int startY, int srcW, int srcH, double scale=1.0);
	void GetWindowSize(int &w, int &h);
	void Flip();
};

#endif