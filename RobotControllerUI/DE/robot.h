#pragma once
#include"Common.h"
#include"global.h"


class Robot
{
public:
	//현재 바라보는 방향 추가
	
	void Move();
	void Rotate();// 90도로 몇번 움직일지
	Robot(Position start, int direction);
	Position getRobotPosition();
	int getRobotDirection();
	int getDirectionIndex();
	//void setRobotPosition(Position p);
private:
	Position rPosition;
	int rDirection;
	int dIndex;
};


class RobotMovementInterface
{
public:
	void RotateRequest(int direction);
	void MoveRequest();
	int getRobotDirection();
	Position getRobotPosition();

	RobotMovementInterface(Position start, int direction);
private:
	Robot* robot;


};

