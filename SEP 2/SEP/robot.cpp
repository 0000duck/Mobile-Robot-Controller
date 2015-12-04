#include<stdio.h>
#include"robot.h"
#include"Common.h"
#include"global.h"
void RobotMovementInterface::MoveRequest(int direction)
{

	int RotateNum=0;
	while (direction != robot->rDirection){
		robot->rDirection = rotateDirection[RotateNum];//90도씩 시계방향으로 돈다.
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
	int temp = 0;	//현재 바라보는 방향에서 
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
	//처음에 아래를 방향으로 한다.
	rPosition = start;
	rDirection = direction;
}

