#pragma once
#include"Common.h"
class VirtualRobot
{
public:

	//void CheckSensingData();
	void VirtualMove();
	//void ComputeOffset();
	void InitVirtualRobot(Position startP);
	VirtualRobot(Position Startp, int direction);
	void virtualRotate(int numOfRotate);
	Position getvPosition();
	int getvDirection();
private:
	Position vPosition;
	int vDirection;
	//int state;
};