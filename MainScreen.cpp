#include "MainScreen.h"

void MainScreen::Start(){
	SDL_Color black={0,0,0};
	std::wstring sServer, sClient;
	sServer=L"��������� ������";
	sClient=L"ϳ����������";
	server=graphics->NewImage(sServer,black);
	client=graphics->NewImage(sClient,black);
}

void MainScreen::Update(){
	graphics->DrawImage(server,0,200);
	graphics->DrawImage(client,200,0);
	graphics->Flip();
}