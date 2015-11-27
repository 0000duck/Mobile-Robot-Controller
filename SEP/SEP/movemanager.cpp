#include"moveManager.h"
#include"global.h"
void MoveManager::InitializeMoveData()
{
	//지혜거받는다.
}
void MoveManager::AnalyzeSensingData()
{
	AnalyzePositioningSensorData();
	AnalyzeColorSensorData();
	AnalyzeHazardSensorData();
}
int MoveManager::CompareCurrentPos()
{
	void* result;
	GetPositioningSensorData(result);
	Position *CP = (Position*)result;

	if ( CP->x== virtualRobot.CurrentPosition.x &&CP->y == virtualRobot.CurrentPosition.y)
		return 0;//정상종료
	else
	{
		return POSITIONING_ERROR;
	}
}
void MoveManager::MakeNextMoveData()
{
	//지혜꺼 다시 돌림
}
void MoveManager::GetNextMoveData()
{
	//결과물에서 보고 함
}

//이거만 따로 있어서 Analyze함수들에서 어떻게 써야할지 모르겠으나 일단 일관성 있게 쓴다.
void MoveManager::GetPositioningSensorData(void *result)//우선 가지고만 있는다.
{
	dataInterface.UseSensor(POSITIONING_SENSOR, result);

	//AnalyzePositioningSensorData(*(Position *)result);//여기서 Analyze까지 할지 안할지 모르겠다
}

MoveManager::MoveManager(int** mapInput)
{

	GetMapModel(mapInput);
	virtualRobot.InitVirtualRobot();	//전역으로 startpoint를 가진다.
}

void MoveManager::Explore()
{
	//여기에서 virtualRobot이 움직임
}

void MoveManager::GetMapModel(int** mapInput)
{
	mapManager.CreateMapModel(mapInput);
}

void MoveManager::AnalyzePositioningSensorData()
{
	if (CompareCurrentPos() != 0)
	{
		//에러 발생 moveBack();
	}
}
void MoveManager::AnalyzeHazardSensorData()//처리까지함
{
	void *result;
	dataInterface.UseSensor(HAZARD_SENSOR, result);//현재는 4방향 다 받아오므로 그와 맞게 함수를 짬
	mapManager.AddHazardPoint(*(int*)result);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface.UseColorSensor(result);
	mapManager.AddColorBlob(*(int*)result);
}