#ifndef CLIENT_H
#define CLIENT_H

#include "Independent.h"
#include "Drawer.h"
#include "Connections.h"

class ClientReceiver{
	shared_ptr<Drawer> drawer;
	shared_ptr<ClientConnection> clientIn;
	bool * stopChecker;
	bool connection;
	Section gameFinished;
	std::vector<Section> map;
public:
	ClientReceiver(shared_ptr<Drawer> drawer, shared_ptr<ClientConnection> clientIn, bool * stopChecker) : drawer(drawer), clientIn(clientIn), stopChecker(stopChecker), connection(true), gameFinished(FREE){}
	bool Connection()const{return connection;}
	void CloseConnection(){clientIn->CloseSocket();}
	void Loop();
	Section IsFinished()const{return gameFinished;}
};

#endif