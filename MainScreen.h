#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "IndependentInclude.h"
#include "Screen.h"
#include "Game.h"

class MainScreen : public Screen {
	Image* server;
	Image* client;

public:
	void Start();
	void Update();
};

#endif