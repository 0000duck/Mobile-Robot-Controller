#pragma once
#include <random>
#include <ctime>
#include <iostream>
#include <functional>
#include"datainterface.h"
#include<list>
#include"VirtualRobot.h"
#include"mapmanager.h"

using namespace std;
class MoveManager
{
public:
	int generator();
	Ran ran;

	//list<MapNode> SearchSpotList;
	list<MapNode> RemainSearchSpotList;
	bool isInit;
	void InitializeMoveData();
	void AnalyzeSensingData();
	int CompareCurrentPos();
	int MakeNextMoveData(int prev);
	void GetNextMoveData(int prev);
	void GetPositioningSensorData(void *result);
	void Explore();
	void setPositioningSensor();	//현재 로봇의 위치로 센서 값을 설정
	void possibleError();
	void InitMoveManager(int  startY, int startX, int mapWidth, int mapHeight);
	MapManager *mapManager;
	void RobotMoveRequest();
	void addExplorationPoint(int y, int x);
	static MoveManager* GetManager()
	{
		if (pInstance == NULL)
		{
			pInstance = new MoveManager();

		}
		return pInstance;
	}
	int getMapData(int y, int x);
	void setMapData(int y, int x, int kind);
private:
	static MoveManager* pInstance;

	MoveManager();

	
	void SetMapModel(int mapWidth, int mapHeight, Position start);
	void AnalyzePositioningSensorData();
	void AnalyzeColorSensorData();
	void AnalyzeHazardSensorData();//이름 바꿈
	void InitDis();
	void CalPath(int x, int y);
	int DisEnd();
	
	int **dis;
	Position getRobotPosition();
	MapModel *mapModel;
	MapNode CurrentTarget;
	MapNode** Map;
	VirtualRobot *virtualRobot;
	Robot *rRobot;
	DataInterface *dataInterface;

};