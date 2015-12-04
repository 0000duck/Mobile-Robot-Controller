#pragma once
#include"Common.h"
#include"global.h"


class Robot
{
public:
	//현재 바라보는 방향 추가
	Position rPosition;
	int rDirection;
	void Move();
	void Rotate(int numOfRotate);// 90도로 몇번 움직일지
	Robot(Position start, int direction);
};


class RobotMovementInterface
{
public:
	void MoveRequest(int direction);
	Robot* robot;
	RobotMovementInterface();
};

