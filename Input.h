#ifndef INPUT_H
#define INPUT_H

#include "IndependentInclude.h"

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

	void StartTextInput();
	void StopTextInput();
	bool TextHandle(std::string &s);
};

#endif