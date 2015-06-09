#ifndef IMAGE_H
#define IMAGE_H

struct SDL_Texture;

class Image
{
private:
	SDL_Texture* texture;
	int w;
	int h;
public:
	friend class Graphics;

	int GetWidth();
	int GetHeight();
};

#endif