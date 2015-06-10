#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "IndependentInclude.h"
#include "Screen.h"
#include "Game.h"
#include "GuiElements.h"

class MainScreen : public Screen {
	shared_ptr<Button> server, client;

public:
	void Start();
	void Update();
};

#endif