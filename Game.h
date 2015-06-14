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
	bool run, stopConnections;


	shared_ptr<Graphics> graphics;
	shared_ptr<Input> input;
	shared_ptr<Screen> mainScreen, connectScreen, serverScreen, gameScreen, serverInput, clientInput, screen;
	shared_ptr<ServerConnection> serverIn, serverOut;
	shared_ptr<ClientConnection> clientIn, clientOut;

	void SetScreen(shared_ptr<Screen> &screen);
	

public:
	Game();
	int Execute(int width, int height, const char *title);
	void ServerMenu(){SetScreen(serverScreen);}
	void ConnectMenu(){SetScreen(connectScreen);}
	void MainMenu(){SetScreen(mainScreen);}
	void CreateServer();
	void StopServer();
	bool ConnectToServer();
	void Exit();

//	
};

#endif