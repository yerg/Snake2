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

		if( evt.key.keysym.sym == SDLK_BACKSPACE && s.length() > 0 ) 
		{ 
			s.pop_back();
			textChanged = true; 
			do {Update();} while (IsKeyDown(SDLK_BACKSPACE));
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
			if ((evt.text.text[0]!=last)||(evt.text.timestamp>time+100))
			{
				s += evt.text.text; 
				textChanged = true;
			}
			time=evt.text.timestamp;
			for(int i=1; i<32; i++) if (evt.text.text[i]=='\0') {last=evt.text.text[i-1]; i=32;}
		} 
	}
	return textChanged;
}

void Input::CheckDirection(Direction &direction){
	if (evt.type == SDL_KEYDOWN) {
		switch (evt.key.keysym.sym)
		{
		case SDLK_UP:
			direction=UP; break;
		case SDLK_RIGHT:
			direction=RIGHT; break;
		case SDLK_DOWN:
			direction=DOWN; break;
		case SDLK_LEFT:
			direction=LEFT; break;
		}
	}
}