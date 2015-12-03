#include"Common.h"

class Robot;

class RobotMovementInterface
{
public:
	int MoveRequest(int direction);
	Robot* robot;
	RobotMovementInterface();
};

class Robot
{
public:
	//���� �ٶ󺸴� ���� �߰�
	Position rPosition;
	int rDirection;
	void Move();
	void Rotate(int numOfRotate);// 90���� ��� ��������
	Robot( Position start, int direction);
}; 