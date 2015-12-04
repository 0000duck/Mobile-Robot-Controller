#pragma once
#include"datainterface.h"
#include<list>
#include"VirtualRobot.h"
#include"mapmanager.h"

using namespace std;
class MoveManager
{
public:
	//list<MapNode> SearchSpotList;
	list<MapNode> RemainSearchSpotList;
	void InitializeMoveData();
	void AnalyzeSensingData();
	int CompareCurrentPos();
	int MakeNextMoveData();
	void GetNextMoveData();
	void GetPositioningSensorData(void *result);
	void Explore();
	void setPositioningSensor();	//현재 로봇의 위치로 센서 값을 설정
	MoveManager();
	MoveManager(int** mpaInput, Position start, int mapWidth, int mapHeight,MapNode exp);
	
	
private:
	bool CheckMoveDataInvalid();

	void InitMoveManager(int** mapInput, Position start, int mapWidth, int mapHeight, MapNode ExP);
	void SetMapModel(int** mpaInput, int mapWidth, int mapHeight, Position start);
	void AnalyzePositioningSensorData();
	void AnalyzeColorSensorData();
	void AnalyzeHazardSensorData();//이름 바꿈
	void InitDis();
	void CalPath(int x, int y);
	void RobotMoveRequest();
	int **dis;
	MapModel *mapModel;
	MapNode CurrentTarget;
	MapNode** Map;
	VirtualRobot *virtualRobot;
	Robot *rRobot;
	DataInterface *dataInterface;
	MapManager *mapManager;
};