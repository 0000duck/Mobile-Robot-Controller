#pragma once
#include "Common.h"
#include "global.h"
#include "VirtualRobot.h"


/*
void VirtualRobot::CheckSensingData()
{
	// 여기서 positioning error 검사
}
*/
void VirtualRobot::VirtualMove()
{
	//여기에 gui를 달 수도 있다.아니면 VirtualMove와 Gui를 동시에 호출할 수도 있다.
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