#ifndef SERVER_H
#define SERVER_H

#include "Independent.h"
#include "Drawer.h"
#include "Connections.h"

class Snake {
	int speed, acc, w, h, lenght, penalty, currentSpeed; 
	Point square[2], head[2];
	std::deque<Direction> body[2];
	std::vector<Section> map;
	Section gameFinished;
	bool connection;

	bool * stopChecker;
	Direction *sMove, *cMove;
	shared_ptr<Drawer> drawer;
	shared_ptr<ServerConnection> serverOut;

	void StartSet();
	void MakeMap();
	void DoNextMove();
	Point CountNext(Point p, const Section &s) const;
	int Position(const Point &p)const;
	bool IsBody(const Point &p)const;
	bool IsOutOfBounds(const Point &p)const;
	Direction Reverse(const Direction &d)const;
	void DoFinish(Section s);
public:
	Snake(shared_ptr<Drawer> drawer, shared_ptr<ServerConnection> serverOut, Settings s,  bool *stopChecker, Direction *sMove, Direction *cMove)
		: drawer(drawer), serverOut(serverOut), w(s.w), h(s.h), lenght(s.lenght), penalty(s.penalty), speed(s.speed), acc(s.acc), stopChecker(stopChecker), sMove(sMove), cMove(cMove), connection(true),gameFinished(FREE){}
	void GameLoop();
	bool Connection()const{return connection;}
	void CloseConnection(){serverOut->CloseSocket();}
	Section IsFinished()const{return gameFinished;}
};

class ServerReceiver {
	shared_ptr<ServerConnection> serverIn;
	bool * stopChecker;
	bool connection;
	Direction cMove;
	Direction message;
public:
	ServerReceiver(shared_ptr<ServerConnection> serverIn, bool *stopChecker) :serverIn(serverIn), stopChecker(stopChecker), cMove(DOWN), connection(true) {}
	bool Connection()const{return connection;}
	void CloseConnection(){serverIn->CloseSocket();}
	Direction* GetDirection(){return &cMove;}
	void Loop();
};

#endif