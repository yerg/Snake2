#ifndef GAME_H
#define GAME_H

#include "Independent.h"
#include "Screen.h"
#include "MenuScreens.h"
#include "Server.h"
#include "Client.h"

class Graphics;
class Input;
class Screen;

class Game
{
private:
	bool run;

	shared_ptr<Graphics> graphics;
	shared_ptr<Input> input;
	shared_ptr<Screen> mainScreen, connectScreen, serverScreen, gameScreen, serverInput, clientInput, screen;
	shared_ptr<Server> serverIn, serverOut;
	shared_ptr<Client> clientIn, clientOut;
	void SetScreen(shared_ptr<Screen> &screen);
public:
	Game();
	int Execute(int width, int height, const char *title);
	void ServerMenu(){SetScreen(serverScreen);}
	void ConnectMenu(){SetScreen(connectScreen);}
	void MainMenu(){SetScreen(mainScreen);}
	void Exit();

	bool
};

#endif