
#include <fstream>
#include <iostream>
#include"moveManager.h"
#include"MainFlow.h"
//paragmaOnce
using namespace std;


MovementInterface::MovementInterface()
{
}

void MovementInterface::init(int startY, int startX, int mapHeight, int mapWidth)
{

	MoveManager::GetManager()->InitMoveManager(startY, startX, mapHeight, mapWidth);

}
void MovementInterface::AddHazardPoint(int y, int x)
{
	MoveManager::GetManager()->mapManager->addHazardPointByPoint(y, x);
}
void MovementInterface::AddColorBlobPoint(int y, int x)
{
	MoveManager::GetManager()->mapManager->addColorBlobPointByPoint(y, x);
}
void MovementInterface::move()
{
	MoveManager::GetManager()->RobotMoveRequest();
}
void MovementInterface::addExplorationPoint(int y, int x)
{
	MoveManager::GetManager()->addExplorationPoint(y, x);
}
void MovementInterface::start()
{
	MoveManager::GetManager()->CSInterfacel->Start();
	MoveManager::GetManager()->Explore();
	
}

