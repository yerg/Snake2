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

class Game
{
private:
	bool run;
    bool stopGameSession;
	SDL_Thread *thClient, *thSnake, *thServer;
	shared_ptr<Graphics> graphics;
	shared_ptr<Input> input;
	shared_ptr<Screen> mainScreen, connectScreen, serverScreen, gameScreen, serverInput, clientInput, screen;
	shared_ptr<ServerConnection> serverIn, serverOut;
	shared_ptr<ClientConnection> clientIn, clientOut;
	shared_ptr<ClientReciever> clientReciever;
	shared_ptr<ServerReciever> serverReciever;
	shared_ptr<Snake> snake;
	shared_ptr<Drawer> drawer;

	int tmp, countConnections;
	int w, h, lenght, penalty, speed, acc;
	void SetScreen(shared_ptr<Screen> &screen);
	

public:
	Game();
	int Execute(int width, int height, const char *title);
	void ServerMenu(){SetScreen(serverScreen); countConnections=0;}
	void ConnectMenu(){SetScreen(connectScreen);}
	void MainMenu(){SetScreen(mainScreen);}
	void CreateServer(int w, int h, int lenght, int penalty, int speed, int acc);
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