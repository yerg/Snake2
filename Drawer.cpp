#include "Drawer.h"

Drawer::Drawer(Graphics *graphics) : graphics(graphics) {
	map = graphics->NewImage("img\snake.bmp");
}

void Drawer::Set(int w, int h, int penalty, int lenght){
	this->w=w; 
	this->h=h; 
	SDL_Color grey={50,50,50};

	std::wstring wpen, wlen;
	wlen=L"Довжина змійки, необхідна для перемоги, складає: ";
	wlen.append(std::to_wstring(static_cast<long long>(lenght)));
	wpen=L"Штраф складає: ";
	wpen.append(std::to_wstring(static_cast<long long>(penalty)));

	if (!initialized) 
	{
		initialized=true;
	}
	else
	{
		graphics->DestroyImage(this->lenght);
		graphics->DestroyImage(this->penalty);
	}
	this->lenght=graphics->NewImage(wlen,grey);
	this->lenght=graphics->NewImage(wlen,grey);
}

void Drawer::Draw(Section* letter){
	int baseX=0, baseY=0, side=map->GetHeight();
	for(int i=0; i<h*w; i++)
	{
		graphics->DrawImage(map,baseX+static_cast<int>(i%w)*side,baseY+static_cast<int>(i/w)*side,0,side*i,side,side);
	}
	graphics->DrawImage(lenght,15,15);
	graphics->DrawImage(penalty,15,45);
	graphics->Flip();
}