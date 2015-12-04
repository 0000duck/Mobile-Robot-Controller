#include"Common.h"
#include"global.h"
#include"map.h"
#include"mapmanager.h"
#include"VirtualRobot.h"
#include<list>
#include"datainterface.h"
#include"moveManager.h"

using namespace std;
#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
	dis[CurrentTarget.PosY][CurrentTarget.PosX]=0;
	CalPath(CurrentTarget.PosX, CurrentTarget.PosY);

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

	if(mapManager->mapModel->Map[x][y].data.kind==HAZARD);						//hazard�� ������� ����.
	else 
	{
		if ((i != mapManager->mapWidth-1)&&(dis[j][i+1]>dis[j][i] + 1))			//������ �˻�
			{
				if(mapManager->mapModel->Map[j][i+1].kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(i+1, j);
				}
			}
			if ((i != 0)&&(dis[j][i-1]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManager->mapModel->Map[j][i-1].kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(i-1, j);
				}
			}
			if ((j != mapManager->mapHeight-1)&&(dis[j+1][i]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManager->mapModel->Map[j+1][i].kind==HAZARD);
				else
				{
					dis[j+1][i] = dis[j][i] + 1;
					CalPath(i, j+1);
				}
			}
			if ((j != 0)&&(dis[j-1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if(mapManager->mapModel->Map[j-1][i].kind==HAZARD);
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
	void* result;
	GetPositioningSensorData(result);
	Position *CP = (Position*)result;
	robotPos = *CP;
	if ( CP->x== virtualRobot->vPosition.x &&CP->y == virtualRobot->vPosition.y)
		return 0;//��������
	else
	{
		return POSITIONING_ERROR;
	}
}
int MoveManager::MakeNextMoveData()					//�� �״�� ���� ������ �����ϴ� ��
{
	int val, dir;

	val = dis[robotPos.y][robotPos.x];
	while (true)
	{
		if (val == dis[robotPos.y + 1][robotPos.x] + 1)
			dir=8;
		else if (val == dis[robotPos.y][robotPos.x + 1] + 1)
			dir=6;
		else if (val == dis[robotPos.y - 1][robotPos.x] + 1)
			dir=2;
		else if (val == dis[robotPos.y][robotPos.x - 1] + 1)
			dir=4;
		else
			val++;
	}



}
void MoveManager::GetNextMoveData()					//������ �������� �κ��� ������ ��
{
	int MData;

	MData=MakeNextMoveData();
	virtualRobot->vDirection = MData;

	dataInterface->robotMovementInterface->MoveRequest(MData);


}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput, Position start)
{
	robotPos = start;
	dataInterface = new DataInterface();
	virtualRobot = new VirtualRobot(start);
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);// 2�� ó�� �ٶ󺸴� ������ 2�� �����̶�� ��
	
	SetMapModel(mapInput,mapWidth, mapHeight, start);
}



void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size > 0)					//��� ��ǥ������ Ž���ϴ� ����
	{
		InitializeMoveData();

		while ((robotPos.x != CurrentTarget.PosX) || (robotPos.y != CurrentTarget.PosY))				//�� ��ǥ������ Ž���ϴ� ����
		{
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);
			
		
			while (Forward.data.kind == HAZARD)					//�տ� �ִ� ��尡 Hazard�� �ƴҶ����� ȸ��.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);
				AnalyzeHazardSensorData();
			}

			dataInterface->robotMovementInterface->robot->Move();//���� �κ� move
			virtualRobot->VirtualMove();

		}

		RemainSearchSpotList.pop_front();					//Ž�簡 �Ϸ�Ǿ����� ����Ʈ���� ����
		
		for (i = 0; i < mapManager->mapHeight; i++)			//�Ҵ���� �޸� �ݳ�
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::SetMapModel(int** mapInput, int mapWidth, int mapHeight, Position start)
{
	mapManager = new MapManager(mapInput, mapWidth, mapHeight, start);
}

void MoveManager::AnalyzePositioningSensorData()
{
	if (CompareCurrentPos() != 0)
	{
		//���� ���������� ��
	}
}
void MoveManager::AnalyzeHazardSensorData()//ó��������
{
	void *result;
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);
	mapManager->AddHazardPoint(*(int*)result, robotPos);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface->UseColorSensor(result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition);
	mapManager->AddColorBlob(*(int*)result, robotPos);
}