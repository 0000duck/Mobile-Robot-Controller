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


///���� ����
void VirtualRobot::VirtualMove()
{
	//���⿡ gui�� �� ���� �ִ�.�ƴϸ� VirtualMove�� Gui�� ���ÿ� ȣ���� ���� �ִ�.
	if (vDirection == 8)
		vPosition.y--;
	if (vDirection == 4)
		vPosition.x--;
	if (vDirection == 2)
		vPosition.y++;
	if (vDirection == 6)
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