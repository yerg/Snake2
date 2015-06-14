#ifndef GAMESCREENS_H
#define GAMESCREENS_H


#include "Independent.h"
#include "Connections.h"
#include "Screen.h"
#include "Game.h"

class ServerInput : public Screen {
	Direction newDirection, direction, finish;
public: 
	void Update();
	void Start();
	const Direction* GetDirection()const{return &direction;}
};

class ClientInput : public Screen{
	shared_ptr<ClientConnection> clientOut;
	Direction last, direction, finish;
public:
	void Update();
	void Start();
};


#endif