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

	dis = (int**)malloc((sizeof(int)*mapManager->mapWidth*mapManager->mapHeight));	//	mapWidth, height�� �켱 �۷ι��� ������ �ִ�.

	for (i = 0; i < mapManager->mapHeight; i++)
	{
		dis[i] = (int*)malloc((sizeof(int)*mapManager->mapWidth));
	}
	
	for (j = 0; j<mapManager->mapHeight; j++)
	{
		for(i=0; i<mapManager->mapWidth; i++)
			dis[j][i]=UNKNOWN;
	}

	CurrentTarget = RemainSearchSpotList.front();

}

void MoveManager::CalPath(int x, int y)							//��忡�� ��ǥ���������� �Ÿ��� ����ϴ� �κ�. ������ ��� �뵵�θ� ���� ��.
{
	int i=x, j=y;

	if(Map[y][x].data.kind==HAZARD);						//hazard�� ������� ����.
	else 
	{
		if ((i != mapManager->mapWidth-1)&&(dis[j][i+1]>dis[j][i] + 1))			//������ �˻�
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
			if ((j != mapManager->mapHeight-1)&&(dis[j+1][i]>dis[j][i] + 1))			//���� �˻�
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

	if ( (CP->x== virtualRobot->vPosition.x )&&(CP->y == virtualRobot->vPosition.y))
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

	val = dis[rRobot->rPosition.y][rRobot->rPosition.x];
	while (true)
	{
		if (val == dis[rRobot->rPosition.y + 1][rRobot->rPosition.x] + 1)
			return 2;
		else if (val == dis[rRobot->rPosition.y][rRobot->rPosition.x + 1] + 1)
			return 6;
		else if ((rRobot->rPosition.y>0)&&(val == dis[rRobot->rPosition.y - 1][rRobot->rPosition.x] + 1))
			return 8;
		else if ((rRobot->rPosition.x>0)&&(val == dis[rRobot->rPosition.y][rRobot->rPosition.x - 1] + 1))
			return 4;
		else
			val++;
	}



}
void MoveManager::GetNextMoveData()					//������ �������� �κ��� ������ ��
{
	int MData;

	MData=MakeNextMoveData();

	virtualRobot->vDirection = MData;
	dataInterface->robotMovementInterface->RotateRequest(MData);

}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, rRobot->rPosition, rRobot->rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput, Position start,int mapWidth, int mapHeight, MapNode ExP)
{
	InitMoveManager(mapInput, start, mapWidth, mapHeight, ExP);
}

void MoveManager::InitMoveManager(int** mapInput, Position start, int mapWidth, int mapHeight, MapNode ExP)
{
	dataInterface = new DataInterface(start);
	virtualRobot = new VirtualRobot(start);
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);// 2�� ó�� �ٶ󺸴� ������ 2�� �����̶�� ��
	SetMapModel(mapInput, mapWidth, mapHeight, start);
	RemainSearchSpotList.push_front(ExP);
	rRobot = dataInterface->robotMovementInterface->robot;
	Map = mapManager->mapModel->Map;
}

void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size() > 0)					//��� ��ǥ������ Ž���ϴ� ����
	{
		InitializeMoveData();

		while ((rRobot->rPosition.x != CurrentTarget.position.x) || (rRobot->rPosition.y != CurrentTarget.position.y))				//�� ��ǥ������ Ž���ϴ� ����
		{

			printf(" (%d,%d) \n", rRobot->rPosition.y, rRobot->rPosition.x);
			for (int j = 0; j < mapManager->mapHeight; j++)
			{
				for (int k = 0; k < mapManager->mapWidth; k++)
				{
					printf("%d ", Map[j][k].data.kind);
				}
				printf("\n");
			}
			
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager->GetForwardMapNode(rRobot->rPosition, rRobot->rDirection);
			
		
			while (Forward.data.kind == HAZARD)					//�տ� �ִ� ��尡 Hazard�� �ƴҶ����� ȸ��.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(rRobot->rPosition, rRobot->rDirection);
				AnalyzeHazardSensorData();
			}
			//���� �ִ����� ǥ����
			RobotMoveRequest();

		}

		RemainSearchSpotList.pop_front();					//Ž�簡 �Ϸ�Ǿ����� ����Ʈ���� ����
		
		for (i = 0; i < mapManager->mapHeight; i++)			//�Ҵ���� �޸� �ݳ�
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::RobotMoveRequest()
{
	//���� ��ġ�� ����
	mapManager->PreviousNode.position.x = rRobot->rPosition.x;
	mapManager->PreviousNode.position.y = rRobot->rPosition.y;
	
	
	//���� ������ �߰�(PositioningSensor*)
	//���� �κ� ��ġ ����
	dataInterface->robotMovementInterface->MoveRequest();
	dynamic_cast<PositioningSensor *>(dataInterface->sensorSystem->Sensors[2])->SetPosition(rRobot->rPosition);
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
		int tx = mapManager->PreviousNode.position.x, ty = mapManager->PreviousNode.position.y;
		if (CompareCurrentPos() != 0)
		{
			//���� ���������� ��
			if (tx == rRobot->rPosition.x){
				if (ty > rRobot->rPosition.y)
				{
					rot = 2;

				}
				else
				{
					rot = 8;
				}
			}
			else if (tx > rRobot->rPosition.x)
			{
				rot = 6;
			}
			else rot = 4;
			if (rot == 0)
				printf("error \n");
			dataInterface->robotMovementInterface->RotateRequest(rot);
			RobotMoveRequest();
			virtualRobot->virtualRotate(rot);

		}
	}
}
void MoveManager::AnalyzeHazardSensorData()//ó��������
{
	void *result = new void*;
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapManager->mapModel, rRobot->rPosition, rRobot->rDirection);
	mapManager->AddHazardPoint(*(int*)result, rRobot->rPosition);
	delete result;
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result = new void*;
	dataInterface->UseColorSensor(result, mapManager->mapModel, rRobot->rPosition);
	mapManager->AddColorBlob(*(int*)result, rRobot->rPosition);
	delete result;
}