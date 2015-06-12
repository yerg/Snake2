#include "MenuScreens.h"

void ServerScreen::Start(){
	SDL_Color black={0,0,0};
	SDL_Color grey={50,50,50};
	
	if(!initialized)
	{
		InitButton(make,L"Створити сервер",black,100,500);
		InitButton(wait,L"Чекаємо...",grey,340,500);
		InitButton(start,L"Розпочати",black,100,550);
		InitButton(back,L"Назад",black,500,500);
		InitSetter(height,L"Висота поля:",200,20,20,25);
		InitSetter(width,L"Ширина поля:",250,25,10,45,5);
		InitSetter(lenght,L"Довжина змійки, що необхідна для перемоги:",300,15,15,50);
		InitSetter(penalty,L"Штраф довжини:",350,10,1,50);
		InitSetter(speed,L"Швидкість руху змійки:",400,1,1,15);
		InitSetter(acceleration,L"Збільшення швидкості руху змійки:",450,1,0,5);
		initialized=true;
	}
	ReDraw();
}

void ServerScreen::ReDraw(){
	DrawSetter(acceleration);
	DrawSetter(height);
	DrawSetter(lenght);
	DrawSetter(penalty);
	DrawSetter(speed);
	DrawSetter(width);
	Draw(make);
	Draw(wait);
	Draw(start);
	Draw(back);
	graphics->Flip();
}

void ServerScreen::Update(){
	HandleLeftClick();
}

void ServerScreen::LeftClick(){
	if(back->CheckHit(coords)) game->MainMenu();
	else if (CheckHitSetter(acceleration));
	else if (CheckHitSetter(height));
	else if (CheckHitSetter(width));
	else if (CheckHitSetter(speed));
	else if (CheckHitSetter(lenght));
	else if (CheckHitSetter(penalty));
}

bool ServerScreen::CheckHitSetter(shared_ptr<Setter> &setter){
	SDL_Color red={200,0,0};
	if((setter->minus)->CheckHit(coords))
	{
		if(setter->value - setter->pace >= setter->min)
		{
			setter->value -= setter->pace;
			graphics->DestroyImage((setter->field)->GetImage());
			temp=std::to_wstring(static_cast<long long>(setter->value));
			(setter->field)->SetImage(graphics->NewImage(temp,red));
			ReDraw();
			return true;
		}
	} 
	if ((setter->plus)->CheckHit(coords))
	{
		if(setter->value + setter->pace <= setter->max)
		{
			setter->value += setter->pace;
			graphics->DestroyImage((setter->field)->GetImage());
			temp=std::to_wstring(static_cast<long long>(setter->value));
			(setter->field)->SetImage(graphics->NewImage(temp,red));
			ReDraw();
			return true;
		}
	}
	return false;
}

void ServerScreen::InitSetter(shared_ptr<Setter> &setter, const wchar_t* text, int y, int value, int min, int max, int pace){
	setter=make_shared<Setter>();
	SDL_Color red={200,0,0};
	SDL_Color grey={50,50,50};
	SDL_Color black={0,0,0};
	setter->value=value;
	setter->min=min;
	setter->max=max;
	setter->pace=pace;
	InitButton(setter->info,text,grey, 40, y);
	InitButton(setter->minus,L"-",black,660,y);
	InitButton(setter->plus,L"+",black,730,y);
	InitButton(setter->field,std::to_wstring(static_cast<long long>(setter->value)),red,680,y);
}

void ServerScreen::DrawSetter(shared_ptr<Setter> &setter){
	Draw(setter->info);
	Draw(setter->field);
	Draw(setter->plus);
	Draw(setter->minus);
}