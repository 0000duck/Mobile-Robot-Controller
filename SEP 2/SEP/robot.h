#include"Common.h"

class RobotMovementInterface
{
public:
	int MoveRequest(int direction);
	Robot robot;
};

class Robot
{
public:
	//���� �ٶ󺸴� ���� �߰�
	int CurrentDirection;
	Position robotPosition;
	void Move();
	void Rotate(int numOfRotate);// 90���� ��� ��������
	Robot(Position start);
}; 