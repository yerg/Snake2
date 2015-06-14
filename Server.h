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

	const bool * stopChecker;
	const Direction *sMove, *cMove;
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
	Snake(shared_ptr<Drawer> drawer, shared_ptr<ServerConnection> serverOut, int w, int h, int lenght, int penalty, int speed, int acc,  const bool *stopChecker, const Direction *sMove, const Direction *cMove)
		: drawer(drawer), serverOut(serverOut), w(w), h(h), lenght(lenght), penalty(penalty), speed(speed), acc(acc), stopChecker(stopChecker), sMove(sMove), cMove(cMove), connection(true)
	{
		StartSet();
	}
	void GameLoop();
	bool Connection()const{return connection;}
	void CloseConnection(){serverOut->CloseConnection();}
	Section IsFinished()const{return gameFinished;}
};

class ServerReciever {
	shared_ptr<ServerConnection> serverIn;
	const bool * stopChecker;
	bool connection;
	Direction cMove;
	std::vector<Direction> message;
public:
	ServerReciever(shared_ptr<ServerConnection> serverIn, const bool *stopChecker) :serverIn(serverIn), stopChecker(stopChecker), cMove(DOWN), connection(true) {}
	bool Connection()const{return connection;}
	void CloseConnection(){serverIn->CloseConnection();}
	const Direction* GetDirection()const{return &cMove;}
	void Loop();
};

#endif