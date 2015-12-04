#include"satellite.h"

void Satellite::setPosition(int dx, int dy)
{
	RobotPosition.x += dx;
	RobotPosition.y += dy;
}