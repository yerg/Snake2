#ifndef INDEPENDENT_H
#define INDEPENDENT_H


#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <memory>
#include

typedef unsigned char byte;
using std::shared_ptr;
using std::make_shared;

struct Point{
	int x;
	int y;
	Point(){}
	Point(int x, int y) : x(x), y(y){}
};

enum Section : char
{
	FREE,
	SQUARE,
	HEAD_LR,
	HEAD_UD,
	HEAD_RL,
	HEAD_DU,
	BODY_UD,
	BODY_LR,
	BODY_DL,
	BODY_LU,
	BODY_UR,
	BODY_RD,
	NECK_LR_1,
	NECK_UD_1,
	NECK_RL_1,
	NECK_DU_1,
	NECK_LD_1,
	NECK_UL_1,
	NECK_RU_1,
	NECK_DR_1,
	NECK_RD_1,
	NECK_DL_1,
	NECK_LU_1,
	NECK_UR_1,
	TAIL_LR_1,
	TAIL_UD_1,
	TAIL_RL_1,
	TAIL_DU_1,
	NECK_LR_2,
	NECK_UD_2,
	NECK_RL_2,
	NECK_DU_2,
	NECK_LD_2,
	NECK_UL_2,
	NECK_RU_2,
	NECK_DR_2,
	NECK_RD_2,
	NECK_DL_2,
	NECK_LU_2,
	NECK_UR_2,
	TAIL_LR_2,
	TAIL_UD_2,
	TAIL_RL_2,
	TAIL_DU_2,
	WIN_1,
	WIN_2,
	DRAW,
	UP,
	RIGHT,
	DOWN,
	LEFT
};
typedef Section Direction;
#endif