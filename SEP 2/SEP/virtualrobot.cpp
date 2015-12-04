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
	vDirection = 2;
}

VirtualRobot::VirtualRobot(Position Startp)
{
	InitVirtualRobot(Startp);
}

