#ifndef MENUSCREENS_H
#define MENUSCREENS_H

#include "Independent.h"
#include "Screen.h"
#include "Game.h"
#include "GuiElements.h"


class MainScreen : public Screen {
	shared_ptr<Button> server, client, exit;
	
	void LeftClick();
public:
	void Start();
	void Update();
};


class ConnectScreen : public Screen {
	shared_ptr<Button> accept, back, connect, box, field, clear, fail, process;
	bool processInd, failInd;
	std::string ipString;
	std::wstring temp;
	void ReDraw();
	void ReFillIpString();
	void LeftClick();
public:
	void Start();
	void Update();
};

class ServerScreen : public Screen {
	struct Setter {
		shared_ptr<Button> info, plus, minus, field; 
		int value, min, max, pace;
	};

	shared_ptr<Button> back, make, wait;
	shared_ptr<Setter> height, width, lenght, penalty, speed, acceleration;
	bool started;
	std::wstring temp;
	void LeftClick();
	void InitSetter(shared_ptr<Setter> &setter, const wchar_t* text, int y, int value, int min, int max, int pace=1);
	void DrawSetter(shared_ptr<Setter> &setter);
	bool CheckHitSetter(shared_ptr<Setter> &setter);
	void ReDraw();
public:
	void Start();
	void Update();
};

#endif