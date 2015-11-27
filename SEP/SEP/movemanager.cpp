#include"moveManager.h"
#include"global.h"
void MoveManager::InitializeMoveData()
{
	//�����Ź޴´�.
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
		return 0;//��������
	else
	{
		return POSITIONING_ERROR;
	}
}
void MoveManager::MakeNextMoveData()
{
	//������ �ٽ� ����
}
void MoveManager::GetNextMoveData()
{
	//��������� ���� ��
}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface.UseSensor(POSITIONING_SENSOR, result);

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput)
{

	GetMapModel(mapInput);
	virtualRobot.InitVirtualRobot();	//�������� startpoint�� ������.
}

void MoveManager::Explore()
{
	//���⿡�� virtualRobot�� ������
}

void MoveManager::GetMapModel(int** mapInput)
{
	mapManager.CreateMapModel(mapInput);
}

void MoveManager::AnalyzePositioningSensorData()
{
	if (CompareCurrentPos() != 0)
	{
		//���� �߻� moveBack();
	}
}
void MoveManager::AnalyzeHazardSensorData()//ó��������
{
	void *result;
	dataInterface.UseSensor(HAZARD_SENSOR, result);//����� 4���� �� �޾ƿ��Ƿ� �׿� �°� �Լ��� «
	mapManager.AddHazardPoint(*(int*)result);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface.UseColorSensor(result);
	mapManager.AddColorBlob(*(int*)result);
}