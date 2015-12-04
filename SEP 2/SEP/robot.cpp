
#include<stdio.h>
#include <random>
#include <ctime>
#include <iostream>
#include <functional>
#include"robot.h"
#include"Common.h"
#include"global.h"
using namespace std;
using namespace std::tr1;
void RobotMovementInterface::RotateRequest(int direction)
{
	int dr = robot->rDirection;
	if (dr == direction)
		return;
	for (int i = 1; i < 4; i++)
	{
		robot->Rotate();
		if (direction == rotateDirection[((robot->dIndex) % 4)]){
			break;
		}
	}
}
void RobotMovementInterface::MoveRequest()
{

	/*
	mt19937 engine((unsigned int)time(NULL));                    // MT19937 ���� ����
	uniform_int_distribution<int> distribution(0, 100);       // ���� ����
	auto generator = bind(distribution, engine);
	if (generator()<20&&(robot->rPosition.x>0&&robot->rPosition.y>0))
		robot->Move();
		*/
	robot->Move();
}

RobotMovementInterface::RobotMovementInterface()
{
}

void Robot::Move()
{
	switch (rDirection)
	{
	case 8:
		rPosition.y--;
		break;
	case 2:
		rPosition.y++;
		break;
	case 4:
		rPosition.x--;
		break;
	case 6:
		rPosition.x++;
		break;
	}
}

void Robot::Rotate()
{
	
	rDirection = rotateDirection[(dIndex+1)%4];
	dIndex = (dIndex + 1) % 4;
}

Robot::Robot(Position start, int direction)
{
	//ó���� �Ʒ��� �������� �Ѵ�.
	rPosition = start;
	rDirection = direction;
	for (int i = 0; i < POSSIBLEDIRECTION; i++)
	{
		if (rotateDirection[i] == rDirection)
			dIndex = i;
	}
}

