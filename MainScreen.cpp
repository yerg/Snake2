#include "MenuScreens.h"


void MainScreen::Start(){
	SDL_Color black={0,0,0};
	if(!initialized)
	{
		InitButton(server,L"Запустити сервер",black,40,200);
		InitButton(client,L"Підключитися",black,40,250);
		InitButton(exit,L"Покинути гру",black,40, 300);
		initialized=true;
	}

}

void MainScreen::Update(){
	Draw(server);		// Window is made slowly.
	Draw(client);		// 
	Draw(exit);			//
	graphics->Flip();	// We will get black window if we move this part into Start().

	HandleLeftClick();
}

void MainScreen::LeftClick(){
	if(server->CheckHit(coords)) game->ServerMenu();
	else if(client->CheckHit(coords)) game->ConnectMenu();
	else if(exit->CheckHit(coords)) game->Exit();
}

