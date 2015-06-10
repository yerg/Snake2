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

void Screen::Start()
{

}

void Screen::Update()
{

}

void Screen::Destroy()
{

}
