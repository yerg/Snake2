#include "Game.h"

Game::Game()
{
	run = true;
}

int Game::Execute(int width, int height, const char *title)
{
	graphics = std::make_shared<Graphics>(width, height, title);
	input = std::make_shared<Input>();
	mainScreen = std::make_shared<MainScreen>();
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