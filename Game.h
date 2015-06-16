#ifndef GAME_H
#define GAME_H

#include "Independent.h"
#include "Screen.h"
#include "MenuScreens.h"
#include "GameScreens.h"
#include "Server.h"
#include "Client.h"
#include <boost/bind.hpp>

int ThreadClient(void * data);
int ThreadSnake(void * data);
int ThreadServer(void * data);
void HandleAccept(int* count, const boost::system::error_code & err);

class ServerInput;
class ClientInput;

class Game
{
private:
	bool run;
    bool stopGameSession;
	SDL_Thread *thClient, *thSnake, *thServer;
	shared_ptr<Graphics> graphics;
	shared_ptr<Input> input;
	ServerInput * rawServerInput;
	ClientInput * rawClientInput;
	shared_ptr<Screen> mainScreen, connectScreen, serverScreen, gameScreen, serverInput, clientInput, screen;
	shared_ptr<ServerConnection> serverIn, serverOut;
	shared_ptr<ClientConnection> clientIn, clientOut;
	shared_ptr<ClientReceiver> clientReceiver;
	shared_ptr<ServerReceiver> serverReceiver;
	shared_ptr<Snake> snake;
	shared_ptr<Drawer> drawer;

	int tmp, countConnections;
	Settings settings;
	void SetScreen(shared_ptr<Screen> screen);
	

public:
	Game() : thServer(NULL), thSnake(NULL), thClient(NULL), run (true), stopGameSession (true) {}
	int Execute(const char *title);
	void ServerMenu(){SetScreen(serverScreen); countConnections=0;}
	void ConnectMenu(){SetScreen(connectScreen);}
	void MainMenu(){SetScreen(mainScreen);}
	void CreateServer(Settings s);
	void CheckNewConnections();
	void StopServer();
	void CloseServer();
	bool ConnectToServer(std::string ipString);
	void CloseClient();

	void FinalServerMenu(Section s);
	void FinalClientMenu(Section s);
	void Exit();
	~Game(){Exit();}
	bool CheckServerConnections();
	bool CheckClientConnections();
	void StopGameSession(){stopGameSession=true;}
	Section IsServerFinished();
	Section IsClientFinished();


//	
};

#endif