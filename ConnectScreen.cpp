#include "MenuScreens.h"

void ConnectScreen::Start(){
	SDL_Color black={0,0,0}, grey={50,50,50}, red={200,0,0};
	if(!initialized)
	{
		InitButton(connect,L"Підключення. Введіть IP-адресу сервера:",grey,100,200);
		InitButton(accept,L"Підключитися",black,100,350);
		InitButton(back,L"Назад",black,500,350);
		InitButton(field,L" ", red,105,250);
		box=make_shared<Button>(graphics->NewImage("img/box.bmp"),Point(100,245));
		initialized=true;
	}
	ReDraw();
	input->StartTextInput();
}
void ConnectScreen::ReDraw(){
	Draw(connect);
	Draw(accept);
	Draw(back);
	Draw(box);
	Draw(field);
	graphics->Flip();
}
void ConnectScreen::Update(){
	SDL_Color red={200,0,0};
	HandleLeftClick();
	if(input->TextHandle(ipString))
	{
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
}

void ConnectScreen::LeftClick(){
	if(back->CheckHit(coords)) 
	{
		input->StartTextInput();
		game->MainMenu();
	}

}