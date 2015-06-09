#ifndef INPUT_H
#define INPUT_H

#include "IndependentInclude.h"

typedef unsigned char byte;

struct Point{
	int x;
	int y;
};

class Input
{
private:
	SDL_Event evt;
public:
	Input();
	void Update();

	bool IsMouseButtonDown(byte key);
	bool IsMouseButtonUp(byte key);
	Point GetButtonDownCoords();

	bool IsKeyDown(byte key);
	bool IsKeyUp(byte key);
	byte GetPressedKey();

	bool IsExit();
};

#endif