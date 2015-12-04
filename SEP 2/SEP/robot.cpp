#include<stdio.h>
#include"robot.h"
#include"Common.h"
#include"global.h"
void RobotMovementInterface::MoveRequest(int direction)
{

	int RotateNum=0;
	while (direction != robot->rDirection){
		robot->rDirection = rotateDirection[RotateNum];//90���� �ð�������� ����.
		RotateNum++;										//
	}
	robot->Rotate(RotateNum);
	robot->Move();
}

RobotMovementInterface::RobotMovementInterface()
{
}

void Robot::Move()
{
	printf("%d %d",rPosition.x, rPosition.y);
}

void Robot::Rotate(int num)
{
	int temp = 0;	//���� �ٶ󺸴� ���⿡�� 
	for (int i = 0; i < POSSIBLEDIRECTION; i++)
	{
		if (rDirection == rotateDirection[i])
			break;
		else 
			temp++;
	}
	rDirection = rotateDirection[num + temp];
}

Robot::Robot(Position start, int direction)
{
	//ó���� �Ʒ��� �������� �Ѵ�.
	rPosition = start;
	rDirection = direction;
}

