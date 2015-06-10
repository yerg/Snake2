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

	shared_ptr<Graphics> graphics;
	shared_ptr<Input> input;
	shared_ptr<Screen> mainScreen, connectScreen, serverScreen, gameScreen, screen;
	void SetScreen(shared_ptr<Screen> &screen);
public:
	Game();
	int Execute(int width, int height, const char *title);
	void CreateServerMenu(){SetScreen()}
	void ConnectMenu(){}
	void Exit();
};

#endif