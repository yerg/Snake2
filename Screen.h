#ifndef SCREEN_H
#define SCREEN_H

#include "IndependentInclude.h"
#include "Graphics.h"
#include "GuiElements.h"
class Game;
class Input;
class Graphics;

class Screen
{
protected:
	Game* game;
	Input* input;
	Graphics* graphics;
	void Draw(shared_ptr<Button> &button);
public:
	void SetController(Game* game, Input* input, Graphics* graphics);

	virtual void Start();
	virtual void Update();
	virtual void Destroy();
};

#endif
