#include "MainScreen.h"


void MainScreen::Start(){
	SDL_Color black={0,0,0};
	server=make_shared<Button>(graphics->NewImage(L"Запустити сервер",black),Point(200,200));
	client=make_shared<Button>(graphics->NewImage(L"Підключитися",black),Point(200,250));


}

void MainScreen::Update(){
	Draw(server);		// Window makes slowly.
	Draw(client);		// We will get black window if we move this part into Start().
	graphics->Flip();	// ...

	

}

