#pragma once
using namespace std;
#include<list>
#include"datainterface.h"
#include"VirtualRobot.h"
#include"map.h"
#include"mapmanager.h"

class MoveManager
{
public:
	list<MapNode> SearchSpotList;
	list<MapNode> RemainSearchSpotList;
	void InitializeMoveData();
	void AnalyzeSensingData();
	int CompareCurrentPos();
	int MakeNextMoveData();
	void GetNextMoveData();
	void GetPositioningSensorData(void *result);
	void Explore();

	MoveManager();
	MoveManager(int** mpaInput, Position start);
	DataInterface *dataInterface;
	MapManager *mapManager;
	VirtualRobot *virtualRobot;

private:
	bool CheckMoveDataInvalid();

	void SetMapModel(int** mpaInput, int mapWidth, int mapHeight, Position start);
	void AnalyzePositioningSensorData();
	void AnalyzeColorSensorData();
	void AnalyzeHazardSensorData();//¿Ã∏ß πŸ≤ﬁ
	void InitDis();
	void CalPath(int x, int y);
	void CalFirst(int x, int y);
	void CalSecond(int x, int y);
	void CalThird(int x, int y);
	void CalFourth(int x, int y);
	int **dis;
	MapNode CurrentTarget;
	Position robotPos;
};