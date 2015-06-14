#include "Screen.h"

void Screen::SetController(Game* game, Input* input, Graphics* graphics)
{
	this->game = game;
	this->input = input;
	this->graphics = graphics;
}

void Screen::Draw(shared_ptr<Button> &button) {
	graphics->DrawImage(button->GetImage(),button->GetPosition().x,button->GetPosition().y);
}

void Screen::InitButton(shared_ptr<Button> &button, std::wstring text, SDL_Color & color, int x, int y, bool fast){
	button=make_shared<Button>(graphics->NewImage(text,color,fast),Point(x,y));
}

void Screen::HandleLeftClick(){
	if(input->IsMouseButtonDown(1)) {							//Left-click
		while(!(input->IsMouseButtonUp(1))) input->Update();
		coords=input->GetButtonDownCoords();
		LeftClick();
	}
}

void Screen::Start()
{

}

void Screen::Update()
{

}
