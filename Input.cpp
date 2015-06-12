#include "Input.h"

Input::Input(){
	SDL_EventState(SDL_MOUSEMOTION,SDL_DISABLE);
}

void Input::Update()
{
	while(SDL_PollEvent(&evt));
}

bool Input::IsMouseButtonDown(byte key)
{
	if(evt.type == SDL_MOUSEBUTTONDOWN)
		if(evt.button.button == key)
			return true;
	return false;
}

bool Input::IsMouseButtonUp(byte key)
{
	if(evt.type == SDL_MOUSEBUTTONUP)
		if(evt.button.button == key)
			return true;
	return false;
}

Point Input::GetButtonDownCoords()
{
	Point point;
	point.x = evt.button.x;
	point.y = evt.button.y;

	return point;
}

bool Input::IsKeyDown(byte key)
{
	return (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == key);
}

bool Input::IsKeyUp(byte key)
{
	return (evt.type == SDL_KEYUP && evt.key.keysym.sym == key);
}

byte Input::GetPressedKey()
{
	return evt.key.keysym.sym;
}

bool Input::IsExit()
{
	return (evt.type == SDL_QUIT || (evt.type == SDL_WINDOWEVENT ? evt.window.event==SDL_WINDOWEVENT_CLOSE : 0) );
}

void Input::StartTextInput(){
	SDL_StartTextInput();
}

void Input::StopTextInput(){
	SDL_StopTextInput();
}

bool Input::TextHandle(std::string &s){
	bool textChanged = false;
	if( evt.type == SDL_KEYDOWN ) { 
		//Handle backspace 
		if( evt.key.keysym.sym == SDLK_BACKSPACE && s.length() > 0 ) 
		{ 
			//lop off character 
			s.pop_back(); 
			textChanged = true; 
		}  
		else if( evt.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) 
		{ 
			SDL_SetClipboardText( s.c_str() );
		} 
		else if( evt.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) 
		{ 
			s = SDL_GetClipboardText(); 
			textChanged = true; 
		} 
	}
	if( evt.type == SDL_TEXTINPUT ) 
	{ 
		if( !( ( evt.text.text[ 0 ] == 'c' || evt.text.text[ 0 ] == 'C' ) && ( evt.text.text[ 0 ] == 'v' || evt.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ) 
		{ 
			s += evt.text.text; textChanged = true; 
		} 
	}
	return textChanged;
}