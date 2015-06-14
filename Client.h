#ifndef CLIENT_H
#define CLIENT_H

#include "Independent.h"
#include "Drawer.h"
#include "Connections.h"

class ClientReciever{
	shared_ptr<Drawer> drawer;
	shared_ptr<ClientConnection> clientIn;
	const bool * stopChecker;
	bool connection;
	Section gameFinished;
	std::vector<Section> map;
public:
	ClientReciever(shared_ptr<Drawer> drawer, shared_ptr<ClientConnection> clientIn, const bool * stopChecker) : drawer(drawer), clientIn(clientIn), stopChecker(stopChecker), connection(true){}
	bool Connection()const{return connection;}
	void CloseConnection(){clientIn->CloseConnection();}
	void Loop();
	Section IsFinished()const{return gameFinished;}
};

#endif