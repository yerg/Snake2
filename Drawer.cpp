#include "Drawer.h"

Drawer::Drawer(Graphics *graphics) : graphics(graphics), initialized(false) {
	SDL_Color grey={50,50,50};
	map = graphics->NewImage("img/snake.bmp");
	draw = graphics->NewImage(std::wstring(L"нічия"),grey);
	win1 = graphics->NewImage(std::wstring(L"перемога червоної змійки"),grey);
	win2 = graphics->NewImage(std::wstring(L"перемога синьої змійки"),grey);
	finish = graphics->NewImage(std::wstring(L"Гру завершено:"),grey);
}

void Drawer::Set(int w, int h, int penalty, int lenght){
	this->w=w; 
	this->h=h; 
	SDL_Color grey={50,50,50};
	std::wstring wpen, wlen;
	wlen=L"† ";
	wlen.append(std::to_wstring(static_cast<long long>(lenght)));
	wpen=L"— ";
	wpen.append(std::to_wstring(static_cast<long long>(penalty)));
	graphics->Flip();
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
	this->penalty=graphics->NewImage(wpen,grey);
//	graphics->SetResolution(w*map->GetHeight(), h*map->GetHeight())
	// It doesn't work properly here 
}

void Drawer::Draw(std::vector<Section> letter){
	int baseX=0, baseY=0, side=map->GetHeight();
	
	for(int i=0; i<h*w; i++)
	{
		graphics->DrawImage(map,baseX+static_cast<int>(i%w)*side,baseY+static_cast<int>(i/w)*side,letter.at(i+1)*side,0,side,side);
	}
	if (letter.front()!=MAP)
	{
		switch (letter.front()) 
		{
		case DRAW:
			graphics->DrawImage(draw,15,250); break;
		case WIN_1:
			graphics->DrawImage(win1,15,250); break;
		case WIN_2:
			graphics->DrawImage(win2,15,250); break;
		default:
			throw "Bad map key letter";
		}
		graphics->DrawImage(finish,15,200);
		graphics->Flip();
		SDL_Delay(2500);
	} 
	else
	{
		graphics->DrawImage(lenght,15,15);
		graphics->DrawImage(penalty,15,45);
		graphics->Flip();
	}
}