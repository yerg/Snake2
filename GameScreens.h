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
	Direction* GetDirection(){return &direction;}
};

class ClientInput : public Screen{
	ClientConnection* clientOut;
	Direction last, direction, finish;
public:
	void SetConnection(ClientConnection* c) {clientOut=c;}
	void Update();
	void Start();
};


#endif