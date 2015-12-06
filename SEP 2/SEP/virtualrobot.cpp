#pragma once
#include "Common.h"
#include "global.h"
#include "VirtualRobot.h"


/*
void VirtualRobot::CheckSensingData()
{
	// ���⼭ positioning error �˻�
}
*/
void VirtualRobot::VirtualMove()
{
	//���⿡ gui�� �� ���� �ִ�.�ƴϸ� VirtualMove�� Gui�� ���ÿ� ȣ���� ���� �ִ�.
	if (vDirection == UP)
		vPosition.y++;
	if (vDirection == LEFT)
		vPosition.x--;
	if (vDirection == DOWN)
		vPosition.y--;
	if (vDirection == RIGHT)
		vPosition.x++;
}

/*
void VirtualRobot::ComputeOffset()
{
	
}
*/

void VirtualRobot::InitVirtualRobot(Position Startp)
{
	vPosition.x = Startp.x;
	vPosition.y = Startp.y;

}

VirtualRobot::VirtualRobot(Position Startp, int direction)
{
	InitVirtualRobot(Startp);
	vDirection = direction;
}


void VirtualRobot::virtualRotate(int num)
{
	vDirection = num;
}

Position VirtualRobot::getvPosition()
{
	return vPosition;
}
int VirtualRobot::getvDirection()
{
	return vDirection;
}