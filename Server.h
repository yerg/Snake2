#ifndef SERVER_H
#define SERVER_H

#include "Independent.h"
#include "Drawer.h"
#include "Connections.h"
#include "Screen.h"
class Snake {
	int speed, acc, w, h, lenght, penalty, currentSpeed; 
	Point square[2], head[2];
	std::deque<Direction> body[2];
	std::vector<Section> map;
	bool gameFinished;

	const bool * stopChecker;
	const Direction *sMove, *cMove;
	Drawer *drawer;
	shared_ptr<ServerConnection> serverOut;

	void StartSet();
	void MakeMap();
	void DoNextMove();
	Point CountNext(Point p, const Section &s) const;
	int Position(const Point &p)const;
	bool IsBody(const Point &p)const;
	bool IsOutOfBounds(const Point &p)const;
	Direction Reverse(const Direction &d)const;
	void DoWin();
	void DoLose();
	void DoDraw();
public:
	Snake(Drawer *drawer, shared_ptr<ServerConnection> serverOut, int w, int h, int lenght, int penalty, int speed, int acc,  const bool *stopChecker, const Direction *sMove, const Direction *cMove)
		: drawer(drawer), serverOut(serverOut), w(w), h(h), lenght(lenght), penalty(penalty), speed(speed), acc(acc), stopChecker(stopChecker), sMove(sMove), cMove(cMove)
	{
		StartSet();
	}
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