#ifndef CLIENT_H
#define CLIENT_H

#include "Independent.h"
#include "Drawer.h"
#include "Connections.h"
#include "Screen.h"
class ClientInput : public Screen{
	shared_ptr<ClientConnection> clientOut;
	Direction last, direction;
public:
	void Update();
	void Start();
};

class ClientReciever{
	Drawer * drawer;
	shared_ptr<ClientConnection> clientIn;
public:

};

#endif