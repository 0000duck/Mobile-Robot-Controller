#pragma once
#include"Common.h"
class VirtualRobot
{
public:
	Position vPosition;
	int vDirection;
	void CheckSensingData();
	void VirtualMove();
	//void ComputeOffset();
	void InitVirtualRobot(Position startP);
	VirtualRobot(Position Startp);
	void virtualRotate(int numOfRotate);
private:
	//int state;
};
