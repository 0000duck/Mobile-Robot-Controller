#include"VirtualRobot.h"
#include"global.h"

void VirtualRobot::CheckSensingData()
{
	// 뭘하는 걸까이건
}
void VirtualRobot::VirtualMove()
{
	//여기에 gui를 달 수도 있다.아니면 VirtualMove와 Gui를 동시에 호출할 수도 있다.
	if (CurrentDirection == 8)
		CurrentPosition.y--;
	if (CurrentDirection == 4)
		CurrentPosition.x--;
	if (CurrentDirection == 2)
		CurrentPosition.y++;
	if (CurrentDirection == 6)
		CurrentPosition.x++;
}
void VirtualRobot::ComputeOffset()
{
	// ?
}
void VirtualRobot::InitVirtualRobot(Position Startp)
{
	CurrentPosition.x = Startp.x;
	CurrentPosition.y = Startp.y;
	CurrentDirection = 2;
}

VirtualRobot::VirtualRobot()
{
	
}

