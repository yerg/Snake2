#include "MenuScreens.h"

void ServerScreen::Start(){
	SDL_Color black={0,0,0};
	SDL_Color grey={50,50,50};
	started=false;
	if(!initialized)
	{
		InitButton(make,L"�������� ������",black,40,500);
		InitButton(wait,L"������...",grey,340,500);
		InitButton(back,L"�����",black,500,500);
		InitSetter(height,L"������ ����:",200,20,20,25);
		InitSetter(width,L"������ ����:",250,25,10,45,5);
		InitSetter(lenght,L"������� �����, �� ��������� ��� ��������:",300,15,15,50);
		InitSetter(penalty,L"����� �������:",350,10,1,50);
		InitSetter(speed,L"�������� ���� �����, ����� � �������:",400,60,30,240,10);
		InitSetter(acceleration,L"��������� �������� ���� �����:",450,10,0,30,2);
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
	if (started) Draw(wait);
	else Draw(make);
	Draw(back);
	graphics->Flip();
}

void ServerScreen::Update(){
	HandleLeftClick();
	if(input->IsExit()) game->Exit();
	game->CheckNewConnections();
}

void ServerScreen::LeftClick(){
	if(back->CheckHit(coords)) 
	{
		if (started) game->StopServer();
		game->MainMenu();
	}
	else if(!started && make->CheckHit(coords)) 
	{
		game->CreateServer(Settings(width->value, height->value, lenght->value, penalty->value, speed->value, acceleration->value));
		started=true;
		ReDraw();
	}
	else if (!started)
	{
		if (CheckHitSetter(acceleration));
		else if (CheckHitSetter(height));
		else if (CheckHitSetter(width));
		else if (CheckHitSetter(speed));
		else if (CheckHitSetter(lenght));
		else CheckHitSetter(penalty);
	}
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
	if (!started)
	{
		Draw(setter->plus);
		Draw(setter->minus);
	}
}