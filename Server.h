#ifndef SERVER_H
#define SERVER_H

#include "Independent.h"
#include "Drawer.h"
#include "Connections.h"
#include "Screen.h"
class Snake {
	Point square[2], head[2];
	std::deque<Direction> body[2];
	Drawer *drawer;
	shared_ptr<Server> serverOut;
	int speed, acc, w,h, lenght, penalty; 
public:
	void GameLoop();
};

class ServerReciever {

};

class ServerInput : public Screen {

public: 
	void Update();
	void Start();
};

#endif