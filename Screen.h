#ifndef SCREEN_H
#define SCREEN_H

#include "Independent.h"
#include "Graphics.h"
#include "Input.h"
#include "GuiElements.h"
class Game;

class Screen
{
protected:
	Game* game;
	Input* input;
	Graphics* graphics;
	Point coords;
	bool initialized;
	void Draw(shared_ptr<Button> &button);
	void HandleLeftClick();
	virtual void LeftClick(){}
	void InitButton(shared_ptr<Button> &button, std::wstring text, SDL_Color & color, int x, int y, bool fast=false);
public:
	Screen() : initialized(false){}		//?
	void SetController(Game* game, Input* input, Graphics* graphics);

	virtual void Start();
	virtual void Update();
};

#endif
