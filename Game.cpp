#include "Game.h"

Game::Game()
{
	run = true;
	stopConnections=true;
}

int Game::Execute(int width, int height, const char *title)
{
	graphics = make_shared<Graphics>(width, height, title);
	input = make_shared<Input>();
	mainScreen = make_shared<MainScreen>();
	connectScreen = make_shared<ConnectScreen>();
	serverScreen = make_shared<ServerScreen>();

	screen=mainScreen;
	screen->SetController(this,input.get(),graphics.get());

	this->screen->Start();

	while(run)
	{
		input->Update();
		screen->Update();
	}

	screen->Destroy();


	return 0;
}

void Game::SetScreen(shared_ptr<Screen> &screen)
{
	this->screen->Destroy();
	this->screen = screen;
	this->screen->SetController(this,input.get(),graphics.get());
	this->screen->Start();
}

void Game::Exit()
{
	run = false;
}

void Game::CreateServer(){

}

void Game::StopServer(){

}

bool Game::ConnectToServer(){
	SDL_Delay(1300);
	return true;
}