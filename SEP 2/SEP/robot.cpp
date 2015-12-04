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
	robot->Rotate(direction);
}
void RobotMovementInterface::MoveRequest()
{
	//실수로 길을 틀린다.
	/*mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	uniform_int_distribution<int> distribution(0, 100);       // 생성 범위
	auto generator = bind(distribution, engine);
	if (generator() < 10);
		robot->Rotate(generator() % 4);
	*/
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

