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
	//현재 바라보는 방향 추가
	int CurrentDirection;
	Position robotPosition;
	void Move();
	void Rotate(int numOfRotate);// 90도로 몇번 움직일지
	Robot(Position start);
}; 