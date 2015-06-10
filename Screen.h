#ifndef SCREEN_H
#define SCREEN_H

#include <memory>
class Game;
class Input;
class Graphics;

class Screen
{
protected:
	Game* game;
	Input* input;
	Graphics* graphics;
public:
	void SetController(Game* game, Input* input, Graphics* graphics);

	virtual void Start();
	virtual void Update();
	virtual void Destroy();
};

#endif
