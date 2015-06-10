#ifndef GAME_H
#define GAME_H

#include "IndependentInclude.h"
#include "Graphics.h"
#include "Input.h"
#include "Screen.h"
#include "MainScreen.h"

class Graphics;
class Input;
class Screen;

class Game
{
private:
	bool run;

	std::shared_ptr<Graphics> graphics;
	std::shared_ptr<Input> input;
	std::shared_ptr<Screen> screen;
	std::vector<std::shared_ptr<Screen> > 
public:
	Game();
	int Execute(int width, int height, const char *title);
	void SetScreen(Screen* screen);
	void Exit();
};

#endif