#include"Common.h"
#include"global.h"
#include"map.h"
#include"mapmanager.h"
#include"VirtualRobot.h"
#include<list>
#include"datainterface.h"
#include"moveManager.h"
#include<conio.h>
using namespace std;
#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
	dis[CurrentTarget.position.y][CurrentTarget.position.x] = 0;
	CalPath(CurrentTarget.position.x, CurrentTarget.position.y);
}
void MoveManager::InitDis()										//dis �ʱ�ȭ
{
	int i, j;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();

	dis = (int**)malloc((sizeof(int)*mapWidth*mapHeight));	//	mapWidth, height�� �켱 �۷ι��� ������ �ִ�.

	for (i = 0; i < mapHeight; i++)
	{
		dis[i] = (int*)malloc((sizeof(int)*mapWidth));
	}
	
	for (j = 0; j < mapHeight; j++)
	{
		for (i = 0; i<mapWidth; i++)
			dis[j][i]=UNKNOWN;
	}

	CurrentTarget = RemainSearchSpotList.front();

}

void MoveManager::CalPath(int x, int y)							//��忡�� ��ǥ���������� �Ÿ��� ����ϴ� �κ�. ������ ��� �뵵�θ� ���� ��.
{
	int i=x, j=y;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	if(Map[y][x].data.kind==HAZARD);						//hazard�� ������� ����.
	else 
	{
		if ((i != mapWidth - 1) && (dis[j][i + 1]>dis[j][i] + 1))			//������ �˻�
			{
				if (Map[j][i + 1].data.kind == HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(i+1, j);
				}
			}
			if ((i != 0)&&(dis[j][i-1]>dis[j][i] + 1))			//���� �˻�
			{
				if (Map[j][i - 1].data.kind == HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(i-1, j);
				}
			}
			if ((j != mapHeight- 1) && (dis[j + 1][i]>dis[j][i] + 1))			//���� �˻�
			{
				if(Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j+1][i] = dis[j][i] + 1;
					CalPath(i, j+1);
				}
			}
			if ((j != 0)&&(dis[j-1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if (Map[j - 1][i].data.kind == HAZARD);
				else					{
					dis[j-1][i] = dis[j][i] + 1;
					CalPath(i, j-1);
				}
			}
	}
}
/*
void MoveManager::AnalyzeSensingData()
{
	AnalyzePositioningSensorData();
	AnalyzeColorSensorData();
	AnalyzeHazardSensorData();
}
*/


int MoveManager::CompareCurrentPos()
{
	void* result = new void*;
	GetPositioningSensorData(result);
	Position *CP = (Position*)result;

	if ( (CP->x== virtualRobot->getvPosition().x )&&(CP->y == virtualRobot->getvPosition().y))
		return 0;//��������
	else
	{
		return POSITIONING_ERROR;
	}
	delete result;
}
int MoveManager::MakeNextMoveData()					//�� �״�� ���� ������ �����ϴ� ��
{
	int val;
	int robotx = dataInterface->getRobotPosition().x;
	int	roboty = dataInterface->getRobotPosition().y;
	val = dis[roboty][robotx];
	while (true)
	{
		if (val == dis[roboty + 1][robotx] + 1)
			return 2;
		else if (val == dis[roboty][robotx + 1] + 1)
			return 6;
		else if ((roboty>0) && (val == dis[roboty - 1][robotx] + 1))
			return 8;
		else if ((robotx>0) && (val == dis[roboty][robotx - 1] + 1))
			return 4;
		else
			val++;
	}



}
void MoveManager::GetNextMoveData()					//������ �������� �κ��� ������ ��
{
	int MData;

	MData=MakeNextMoveData();

	virtualRobot->virtualRotate(MData);
	dataInterface->requestRobotRotate(MData);

}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapModel, dataInterface->getRobotPosition(), dataInterface->getRobotDirection());

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput, Position start,int mapWidth, int mapHeight, MapNode ExP)
{
	InitMoveManager(mapInput, start, mapWidth, mapHeight, ExP);
}

void MoveManager::InitMoveManager(int** mapInput, Position start, int mapWidth, int mapHeight, MapNode ExP)
{
	dataInterface = new DataInterface(start,2);
	virtualRobot = new VirtualRobot(start,2);;// 2�� ó�� �ٶ󺸴� ������ 2�� �����̶�� ��
	SetMapModel(mapInput, mapWidth, mapHeight, start);
	RemainSearchSpotList.push_front(ExP);
	mapModel = mapManager->getMapModel();
	Map = mapModel->getMapNode();
}

void MoveManager::Explore()
{
	MapNode Forward;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	int i;

	while(RemainSearchSpotList.size() > 0)					//��� ��ǥ������ Ž���ϴ� ����
	{
		InitializeMoveData();

		while ((dataInterface->getRobotPosition().x != CurrentTarget.position.x) || (dataInterface->getRobotPosition().y != CurrentTarget.position.y))				//�� ��ǥ������ Ž���ϴ� ����
		{

			printf(" (%d,%d) \n", dataInterface->getRobotPosition().y, dataInterface->getRobotPosition().x);
			for (int j = 0; j < mapHeight; j++)
			{
				for (int k = 0; k < mapWidth; k++)
				{
					printf("%d ", Map[j][k].data.kind);
				}
				printf("\n");
			}
			
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
			
		
			while (Forward.data.kind == HAZARD)					//�տ� �ִ� ��尡 Hazard�� �ƴҶ����� ȸ��.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
				AnalyzeHazardSensorData();
			}
			//���� �ִ����� ǥ����
			RobotMoveRequest();

		}

		RemainSearchSpotList.pop_front();					//Ž�簡 �Ϸ�Ǿ����� ����Ʈ���� ����
		
		for (i = 0; i < mapHeight; i++)			//�Ҵ���� �޸� �ݳ�
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::RobotMoveRequest()
{
	//���� ��ġ�� ����
	mapManager->setPreviousNode(dataInterface->getRobotPosition());

	
	
	//���� ������ �߰�(PositioningSensor*)
	//���� �κ� ��ġ ����
	dataInterface->requestRobotMove();
	setPositioningSensor();
	virtualRobot->VirtualMove();
	
}

void MoveManager::SetMapModel(int** mapInput, int mapWidth, int mapHeight, Position start)
{

	mapManager = new MapManager(mapInput, mapWidth, mapHeight, start);

}

void MoveManager::AnalyzePositioningSensorData()
{
	if (CompareCurrentPos() == POSITIONING_ERROR){
		int rot = 0;
		int tx = mapManager->getPreviousNode().position.x, ty = mapManager->getPreviousNode().position.y;
		if (CompareCurrentPos() != 0)
		{
			//���� ���������� ��
			if (tx == dataInterface->getRobotPosition().x){
				if (ty > dataInterface->getRobotPosition().y)
				{
					rot = 2;

				}
				else
				{
					rot = 8;
				}
			}
			else if (tx > dataInterface->getRobotPosition().x)
			{
				rot = 6;
			}
			else rot = 4;
			if (rot == 0)
				printf("error \n");
			dataInterface->requestRobotRotate(rot);
			RobotMoveRequest();
			virtualRobot->virtualRotate(rot);

		}
	}
}
void MoveManager::AnalyzeHazardSensorData()//ó��������
{
	void *result = new void*;
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapModel, dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
	mapManager->AddHazardPoint(*(int*)result, dataInterface->getRobotPosition());
	delete result;
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result = new void*;
	dataInterface->UseColorSensor(result, mapModel, dataInterface->getRobotPosition());
	mapManager->AddColorBlob(*(int*)result, dataInterface->getRobotPosition());
	delete result;
}

void MoveManager::setPositioningSensor()
{
	dynamic_cast<PositioningSensor *>(dataInterface->sensorSystem->Sensors[2])->SetPosition(dataInterface->getRobotPosition());
}