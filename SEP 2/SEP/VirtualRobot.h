#include "Common.h"
class VirtualRobot
{
public:
	Position CurrentPosition;
	int CurrentDirection;
	void CheckSensingData();
	void VirtualMove();
	void ComputeOffset();
	void InitVirtualRobot(Position startP);
	VirtualRobot(Position Startp);
private:
	int state;
};