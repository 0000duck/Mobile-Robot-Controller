#include"robot.h"
#include"global.h"
int RobotMovementInterface::MoveRequest(int direction)
{
	int RotateNum=0;
	while (direction != robot.CurrentDirection){
		robot.CurrentDirection = rotateDirection[RotateNum];//90���� �ð�������� ����.
		RotateNum++;										//
	}
	robot.Rotate(RotateNum);
	robot.Move();
}

void Robot::Move()
{
	//���⳪ Rotate�� ������ ������ �߻��ϴ� ���� �־�� ��
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
	int temp = 0;	//���� �ٶ󺸴� ���⿡�� 
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
	//ó���� �Ʒ��� �������� �Ѵ�.
	CurrentDirection = start.direction;
	robotPosition.x = start.x;
	robotPosition.y = start.y;
	robotPosition.direction = CurrentDirection;
}
