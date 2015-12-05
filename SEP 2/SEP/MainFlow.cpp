
#include <fstream>
#include <iostream>
#include"moveManager.h"
//paragmaOnce
using namespace std;

class MovementInterface
{
public :
	MoveManager* m;
	MovementInterface(int startY, int startX, int mapHeight, int mapWidth)
	{
		m = MoveManager::GetManager();
		m->InitMoveManager(startY, startX, mapHeight, mapWidth);
		m->Explore();
	}
	void AddHazardPoint(int y, int x)
	{
		m->mapManager->addHazardPointByPoint(y, x);
	}
	void AddColorBlobPoint(int y, int x)
	{
		m->mapManager->addColorBlobPointByPoint(y, x);
	}
	void move()
	{
		m->RobotMoveRequest();
	}
	void addExplorationPoint(int y, int x)
	{
		m->addExplorationPoint(y, x);
	}
};

