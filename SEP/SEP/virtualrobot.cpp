#include"VirtualRobot.h"
#include"global.h"

void VirtualRobot::CheckSensingData()
{
	// ���ϴ� �ɱ��̰�
}
void VirtualRobot::VirtualMove()
{
	//���⿡ gui�� �� ���� �ִ�.�ƴϸ� VirtualMove�� Gui�� ���ÿ� ȣ���� ���� �ִ�.
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

