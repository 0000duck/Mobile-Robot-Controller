
#include <fstream>
#include <iostream>
#include"moveManager.h"
//paragmaOnce
using namespace std;

class MovementInterface
{
public :
	MoveManager* m;
	void init(int startY, int startX, int mapHeight, int mapWidth)
	{
		m = MoveManager::GetManager();
		m->InitMoveManager(startY, startX, mapHeight, mapWidth);
		
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
	void start()
	{
		m->Explore();
	}
};
int main()
{
	MovementInterface m;
	m.init(3,2 , 15, 15);
	m.addExplorationPoint(4, 5);
	m.addExplorationPoint(10, 12);
	m.addExplorationPoint(3, 0);

	m.start();
}

