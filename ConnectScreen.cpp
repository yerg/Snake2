#include "MenuScreens.h"

void ConnectScreen::Start(){
	SDL_Color black={0,0,0}, grey={50,50,50}, red={200,0,0};
	processInd=false;
	failInd=false;
	if(!initialized)
	{
		InitButton(connect,L"Підключення. Введіть IP-адресу сервера:",grey,40,200);
		InitButton(accept,L"Підключитися",black,40,400);
		InitButton(back,L"Назад",black,500,400);
		InitButton(field,L" ", red,45,250);
		box=make_shared<Button>(graphics->NewImage("img/box.bmp"),Point(40,245));
		InitButton(clear,L"Очистити поле",black,40,300);
		InitButton(process,L"Намагаємося підключитися...",grey,280,300);
		InitButton(fail,L"Не вдалося підключитися",grey,280,300);
		initialized=true;
	}
	ReDraw();
	input->StartTextInput();
}
void ConnectScreen::ReDraw(){
	if (!processInd) Draw(connect);
	if (!processInd) Draw(accept);
	Draw(back);
	Draw(box);
	Draw(field);
	Draw(clear);
	if (failInd) Draw(fail);
	if (processInd) Draw(process);
	graphics->Flip();
}
void ConnectScreen::Update(){
	HandleLeftClick();
	if(input->TextHandle(ipString))	ReFillIpString();
	if(input->IsExit()) game->Exit();
}

void ConnectScreen::LeftClick(){
	if(back->CheckHit(coords)) 
	{
		input->StopTextInput();
		game->MainMenu();
	}
	else if (clear->CheckHit(coords))
	{
		ipString.clear();
		ReFillIpString();
	}
	else if (accept->CheckHit(coords))
	{
		input->StopTextInput();
		failInd=false;
		processInd=true;
		ReDraw();
		failInd=game->ConnectToServer();
		processInd=false;
		ReDraw();
	}
}

void ConnectScreen::ReFillIpString(){
	SDL_Color red={200,0,0};
	graphics->DestroyImage(field->GetImage());
	if (!ipString.empty())
	{
		temp.assign(ipString.begin(),ipString.end());
	}
	else
	{
		temp.assign(L" ");
	}
	field->SetImage(graphics->NewImage(temp,red));
	ReDraw();
}