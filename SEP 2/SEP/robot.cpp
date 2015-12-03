#include"robot.h"
#include"global.h"
int RobotMovementInterface::MoveRequest(int direction)
{
	int RotateNum=0;
	while (direction != robot.CurrentDirection){
		robot.CurrentDirection = rotateDirection[RotateNum];//90도씩 시계방향으로 돈다.
		RotateNum++;										//
	}
	robot.Rotate(RotateNum);
	robot.Move();
}

void Robot::Move()
{
	//여기나 Rotate에 가끔씩 오류를 발생하는 것을 넣어야 함
	if (CurrentDirection == 8)
	{
		robotPosition.y--;
	}
	if (CurrentDirection == 4)
	{
		robotPosition.x--;
	}
	if (CurrentDirection == 2)
	{
		robotPosition.y++;
	}
	if (CurrentDirection == 6)
	{
		robotPosition.x++;
	}
	robotPosition.direction = CurrentDirection;
}

void Robot::Rotate(int num)
{
	int temp = 0;	//현재 바라보는 방향에서 
	for (int i = 0; i < POSSIBLEDIRECTION; i++)
	{
		if (CurrentDirection == rotateDirection[i])
			break;
		else 
			temp++;
	}
	CurrentDirection = rotateDirection[num + temp];
}

Robot::Robot(Position start)
{
	//처음에 아래를 방향으로 한다.
	CurrentDirection = start.direction;
	robotPosition.x = start.x;
	robotPosition.y = start.y;
	robotPosition.direction = CurrentDirection;
}
