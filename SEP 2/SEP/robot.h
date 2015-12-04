#pragma once
#include"Common.h"
#include"global.h"


class Robot
{
public:
	//���� �ٶ󺸴� ���� �߰�
	Position rPosition;
	int rDirection;
	void Move();
	void Rotate(int numOfRotate);// 90���� ��� ��������
	Robot(Position start, int direction);
};


class RobotMovementInterface
{
public:
	void RotateRequest(int direction);
	void MoveRequest();
	Robot* robot;
	RobotMovementInterface();
};

