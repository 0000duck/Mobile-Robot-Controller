#pragma once
#include"Common.h"
#include"global.h"


class Robot
{
public:
	//���� �ٶ󺸴� ���� �߰�
	
	void Move();
	void Rotate();// 90���� ��� ��������
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

