#include "Server.h"

void Snake::StartSet(){
	head[0].Set(7,0);
	body[0].assign(2, DOWN);
	head[1].Set(12,0);
	body[1].assign(2, UP);
	square[0].Set(-1,-1);
	square[1].Set(-1,-1);
	map.resize(h*w+2);
	currentSpeed=speed;
	srand(static_cast<unsigned int>(time(NULL)));
}

void Snake::MakeMap(){
	Section s=FREE;
	Point p(0,0);
	map.assign(h*w+1, s);
	std::string erP="Snake has wrong part";
	std::string erB="Snake has empty body";
	for(int i=0; i<2; i++) 
	{
		//Head
		if (body[i].size()<2) throw erB;
		switch (body[i].at(0)){
		case UP:
			s=HEAD_DU; break;
		case RIGHT:
			s=HEAD_LR; break;
		case DOWN:
			s=HEAD_UD; break;
		case LEFT:
			s=HEAD_RL; break;
		default:
			throw erP;
		}
		map.at(Position(head[i]))=s;

		//Neck
		if (body[i].size()>1) 
		{
			switch (body[i].at(0)){
			case UP:
				switch(body[i].at(1))
				{
				case RIGHT:
					s=NECK_UR_1; break;
				case DOWN:
					s=NECK_UD_1; break;
				case LEFT:
					s=NECK_UL_1; break;
				default:
					throw erP;
				}
				break;
			case RIGHT:
				switch(body[i].at(1))
				{
				case UP:
					s=NECK_RU_1; break;
				case DOWN:
					s=NECK_RD_1; break;
				case LEFT:
					s=NECK_RL_1; break;
				default:
					throw erP;
				}
				break;
			case DOWN:
				switch(body[i].at(1))
				{
				case UP:
					s=NECK_DU_1; break;
				case RIGHT:
					s=NECK_DR_1; break;
				case LEFT:
					s=NECK_DL_1; break;
				default:
					throw erP;
				}
				break;
			case LEFT:
				switch(body[i].at(1))
				{
				case UP:
					s=NECK_LU_1; break;
				case RIGHT:
					s=NECK_LR_1; break;
				case DOWN:
					s=NECK_LD_1; break;
				default:
					throw erP;
				}
				break;
			}
		}
		else //Tailless case
		{
			switch (body[i].at(0)){
			case UP:
				s=NECK_DU_1; break;
			case RIGHT:
				s=NECK_LR_1; break;
			case DOWN:
				s=NECK_UD_1; break;
			case LEFT:
				s=NECK_RL_1; break;
			default:
				throw erP;
			}
		}
		p=CountNext(head[i],body[i].at(0));
		map.at(Position(p)) = i ? static_cast<Section>(16+s) : s;

		//Body

		for (size_t j=2; j<=body[i].size(); j++)
		{
			p=CountNext(p,body[i].at(j-1));
			if (body[i].size()>j)
			{
				switch(body[i].at(j-1))
				{
				case UP:
					switch(body[i].at(j))
					{
					case RIGHT:
						s=BODY_UR; break;
					case DOWN:
						s=BODY_UD; break;
					case LEFT:
						s=BODY_LU; break;
					default:
						throw erP;
					}
					break;
				case RIGHT:
					switch(body[i].at(j))
					{
					case UP:
						s=BODY_UR; break;
					case DOWN:
						s=BODY_RD; break;
					case LEFT:
						s=BODY_RL; break;
					default:
						throw erP;
					}
					break;
				case DOWN:
					switch(body[i].at(j))
					{
					case UP:
						s=BODY_UD; break;
					case RIGHT:
						s=BODY_RD; break;
					case LEFT:
						s=BODY_DL; break;
					default:
						throw erP;
					}
					break;
				case LEFT:
					switch(body[i].at(j))
					{
					case UP:
						s=BODY_LU; break;
					case RIGHT:
						s=BODY_RL; break;
					case DOWN:
						s=BODY_DL; break;
					default:
						throw erP;
					}
					break;
				}
				map.at(Position(p))=s;
			}
			else //Tail
			{
				switch(body[i].at(j-1))
				{
				case UP:
					s=TAIL_UD_1; break;
				case RIGHT:
					s=TAIL_RL_1; break;
				case DOWN:
					s=TAIL_DU_1; break;
				case LEFT:
					s=TAIL_LR_1; break;
				}
				map.at(Position(p)) = i ? static_cast<Section>(16+s) : s;
			}
		}
	}
	// Squares
	int tmp,k;
	if ( (square[0].x < 0) || (square[1].x < 0) ) 
	{
		for (int i=0; i<2; i++)
		{
			tmp=rand() % (h*w-(body[0].size()+body[1].size()+2+i));
			k=0;
			while (map.at(k)!=FREE){
				++k;
			}
			while (tmp){
				++k;
				--tmp;
				while (map.at(k)!=FREE){
					++k;
				}
			}
			square[i].x=k%w;
			square[i].y=k/w;
			map.at(Position(square[i]))=SQUARE;
		}
	}
	else
	{
		map.at(Position(square[0]))=SQUARE;
		map.at(Position(square[1]))=SQUARE;
	}
}

void Snake::DoNextMove(){
	bool doPenalty[2], tailBited=false;
	doPenalty[0]=false;
	doPenalty[1]=false; 
	Point p;
	Point newh[2];
	Direction serverMove = *sMove, clientMove = *cMove;
	newh[0]=CountNext(head[0], serverMove);
	newh[1]=CountNext(head[1], clientMove);
	
	//Out of bounds
	if (IsOutOfBounds(newh[0])) 
	{
		newh[0]=head[0];
		if (IsOutOfBounds(newh[1]))
		{ 
			newh[1]=head[1];
			DoDraw();
		}
		else 
		{
			DoLose();
		}
	}
	else if (IsOutOfBounds(newh[1])) 
	{
		newh[1]=head[1];
		DoWin();
	}

	//Bite head
	else if (newh[0]==newh[1]) 
	{
		doPenalty[0]=true;
		doPenalty[1]=true;
	}

	//Bite neck
	else if (newh[0]==head[1])
	{
		if (newh[1]==head[0])
		{
			doPenalty[0]=true;
			doPenalty[1]=true;
		}
		else DoWin();
	}
	else if (newh[1]==head[0]) DoLose();

	//Bite body
	else 
	{
		if (IsBody(newh[0]))
		{
			p=CountNext(newh[0],body[1].back());
			if (!IsOutOfBounds(p) && (newh[1]!=square[0] || newh[1]!=square[1]) && map.at(Position(p))>=TAIL_LR_2 && map.at(Position(p))<=TAIL_DU_2 )
			{
				body[0].push_back(FREE);
				body[1].pop_back();
				tailBited=true;			// for resolving simultaneously bitten tails
			}
			else doPenalty[0]=true;
		}
		if (IsBody(newh[1]))
		{
			p=CountNext(newh[1],body[0].back());
			if (!IsOutOfBounds(p) && (newh[0]!=square[0] || newh[0]!=square[1]) && map.at(Position(p))>=TAIL_LR_1 && map.at(Position(p))<=TAIL_DU_1 )
			{
				body[1].push_back(FREE);
				body[0].pop_back();
				if (tailBited)
				{
					doPenalty[0]=true;
					doPenalty[1]=true;
				}
			}
			else doPenalty[1]=true;
		}

		//Bite tail
		if (map.at(Position(newh[0]))>=TAIL_LR_2 && map.at(Position(newh[0]))<=TAIL_DU_2 && (newh[1]!=square[0] || newh[1]!=square[1]))
		{
			body[0].push_back(FREE);
			body[1].pop_back();
		}
		else if (map.at(Position(newh[1]))>=TAIL_LR_2 && map.at(Position(newh[1]))<=TAIL_DU_2 && (newh[0]!=square[0] || newh[0]!=square[1]))
		{
			body[1].push_back(FREE);
			body[0].pop_back();
		}
	}

	//Eat square
	if (newh[0]!=square[0] || newh[0]!=square[1])
	{
		body[0].push_back(FREE);
		currentSpeed+=acc;
	}
	if (newh[1]!=square[0] || newh[1]!=square[1])
	{
		body[1].push_back(FREE);
		currentSpeed+=acc;
	}

	//Move snakes
	body[0].pop_back();
	body[1].pop_back();
	head[0]=newh[0];
	head[1]=newh[1];
	body[0].push_front(Reverse(serverMove));
	body[1].push_front(Reverse(clientMove));
	
	//Check finish conditions 
	if(!gameFinished)
	{
		if(doPenalty[0]||doPenalty[1])
		{
			body[0].size()+penalty*doPenalty[1] == body[1].size()+penalty*doPenalty[0] ? DoDraw() : 
				body[0].size()+penalty*doPenalty[1] > body[1].size()+penalty*doPenalty[0] ? DoWin() : DoLose();
		}
		else if (body[0].size()>=lenght-1)
		{
			if (body[1].size()>=lenght-1) DoDraw();
			else DoWin();
		} 
		else if (body[1].size()>=lenght-1) DoLose();
	}
}

void Snake::DoWin(){
	gameFinished=true;
}
void Snake::DoWin(){
	gameFinished=true;
}
void Snake::DoWin(){
	gameFinished=true;
}

Point Snake::CountNext(Point p, const Section &s) const{
	switch (s) {
	case UP:
		p.y+=1; break;
	case RIGHT:
		p.x+=1; break;
	case DOWN:
		p.y-=1; break;
	case LEFT:
		p.x-=1; break;
	default:
		throw "Snake has wrong parts";
	}
//	if (p.x<0 || p.y<0 || p.x>=w || p.y>=h) throw "Snake has cheated coordinates!";
	return p;
}
int Snake::Position(const Point &p)const {
	return p.x + p.y * w + 1;
}
bool Snake::IsOutOfBounds(const Point &p)const{
	return p.x<0 || p.y<0 || p.x>=w || p.y>=h;
}
bool Snake::IsBody(const Point &p)const{
	return (map.at(Position(p))>=BODY_UD && map.at(Position(p))<=NECK_UR_1) || (map.at(Position(p))>=NECK_LR_2 && map.at(Position(p))<=NECK_UR_2);
}
Direction Snake::Reverse(const Direction &d)const{
	Direction r;
	switch (d) {
	case UP:
		r=DOWN; break;
	case RIGHT:
		r=LEFT; break;
	case DOWN:
		r=UP; break;
	case LEFT:
		r=RIGHT; break;
	default:
		throw "Wrong direction";
	}
	return r;
}

void Snake::GameLoop(){
	gameFinished=false;
	currentSpeed=speed;
	MakeMap();
	while (!*stopChecker) {
		serverOut->Send(&map[0],map.size());
		drawer->Draw(map);
		SDL_Delay(60000/currentSpeed);
		DoNextMove();
		MakeMap();
	}
}