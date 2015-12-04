#include"Common.h"
#include"global.h"
#include"map.h"
#include"mapmanager.h"
#include"VirtualRobot.h"
#include<list>
#include"datainterface.h"
#include"moveManager.h"
#include "stdlib.h"

using namespace std;
#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
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
	
	for (i = 1; i<mapManager->mapHeight; i++)
	{
		for(j=1; j<mapManager->mapWidth; j++)
			dis[i][j]=UNKNOWN;
	}

	CurrentTarget = RemainSearchSpotList.front;

}

void CalPath(int x, int y)							//��忡�� ��ǥ���������� �Ÿ��� ����ϴ� �κ�. ������ ��� �뵵�θ� ���� ��.
{
	int i, j;

	if(mapManager->mapModel->Map[x][y].data.kind==HAZARD);						//hazard�� ������� ����.
	else if((dataInterface->robotMovementInterface->robot->rPosition.x>x)&&(dataInterface->robotMovementInterface->robot->rPosition.y>y))						//Current�� �������� x, y�� 3��и鿡 ���� ��
		CalThird(x, y);
	else if ((dataInterface->robotMovementInterface->robot->rPosition.x<x) && (dataInterface->robotMovementInterface->robot->rPosition.y>y))					//Current�� �������� x, y�� 2��и鿡 ���� ��
		CalSecond(x, y);
	else if ((dataInterface->robotMovementInterface->robot->rPosition.x>x) && (dataInterface->robotMovementInterface->robot->rPosition.y<y))					//Current�� �������� x, y�� 4��и鿡 ���� ��
		CalFourth(x, y);
	else if ((dataInterface->robotMovementInterface->robot->rPosition.x<x) && (dataInterface->robotMovementInterface->robot->rPosition.y < y))				//Current�� �������� x, y�� 1��и鿡 ���� ��
		CalFirst(x, y);
	else if(x==dataInterface->robotMovementInterface->robot->rPosition.x)								//Current�� x, y�� x������ �������� �������� ��
	{
		if(y<dataInterface->robotMovementInterface->robot->rPosition.y)					//Current�� �������� x, y�� �Ʒ��ʿ� ���� ��
		{
			for(j=y; j<dataInterface->robotMovementInterface->robot->rPosition.y; j++)
			{
				if(mapManager->mapModel->Map[j+1][x].data.kind==HAZARD);
				else if(dis[j+1][x]>dis[j][x]+1)
					dis[j+1][x]=dis[j][x]+1;
			}
		}
		else										//Current�� �������� x, y�� ���ʿ� ���� ��
		{
			for(j=y; j>dataInterface->robotMovementInterface->robot->rPosition.y; j--)
			{
				if(mapManager->mapModel->Map[j-1][x].data.kind==HAZARD);
				else if(dis[j-1][x]>dis[j][x]+1)
					dis[j-1][x]=dis[j][x]+1;
			}
		}
	}
	else if(y==dataInterface->robotMovementInterface->robot->rPosition.y)								//Current�� x, y�� y������ �������� �������� ��
	{
		if(x<dataInterface->robotMovementInterface->robot->rPosition.x)					//Current�� �������� x, y�� ���ʿ� ���� ��
		{
			for(i=x; i<dataInterface->robotMovementInterface->robot->rPosition.x; i++)
			{
				if(mapManager->mapModel->Map[y][i+1].data.kind==HAZARD);
				else if(dis[y][i+1]>dis[y][i]+1)
					dis[y][i+1]=dis[y][i]+1;
			}
		}
		else										//Current�� �������� x, y�� �����ʿ� ���� ��
		{
			for(i=x; i>dataInterface->robotMovementInterface->robot->rPosition.x; i--)
			{
				if(mapManager->mapModel->Map[y][i-1].data.kind==HAZARD);
				else if(dis[y][i-1]>dis[y][i]+1)
					dis[y][i-1]=dis[y][i]+1;
			}
		}
	}

}
void CalFirst(int x, int y)				//Current�� �������� ��ǥ������ 1��и鿡 ���� ��
{
	int i, j;

	for (i = x; i>dataInterface->robotMovementInterface->robot->rPosition.x; i--)
	{
		for (j = y; j>dataInterface->robotMovementInterface->robot->rPosition.y; j--)
		{
			if ((i != x)&&(dis[j][i+1]>dis[j][i] + 1))			//������ �˻�
			{
				if(mapManager->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i-1]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManager->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != y)&(dis[j+1][i]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&&(dis[j-1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if(mapManage->mapModel->Map[j-1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j-1, i);
				}
			}
		}
	}
}
void CalSecond(int x, int y)				//Current�� �������� ��ǥ������ 2��и鿡 ���� ��
{
	int i, j;

	for (i = x; i<dataInterface->robotMovementInterface->robot->rPosition.x; i++)
	{
		for (j = y; j>dataInterface->robotMovementInterface->robot->rPosition.y; j--)
		{
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i+1]>dis[j][i] + 1))			//������ �˻�
			{
				if(mapManage->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != x)&&(dis[j][i-1]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != y)&(dis[j+1][i]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&&(dis[j-1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if(mapManage->mapModel->Map[j-1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j-1, i);
				}
			}
		}
	}
}
void CalThird(int x, int y)				//Current�� �������� ��ǥ������ 3��и鿡 ���� �� 
{
	int i, j;

	for (i = x; i<dataInterface->robotMovementInterface->robot->rPosition.x; i++)
	{
		for (j = y; j<dataInterface->robotMovementInterface->robot->rPosition.y; j++)
		{
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i+1]>dis[j][i] + 1))			//������ �˻�
			{
				if(mapManage->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != x)&&(dis[j][i-1]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&(dis[j+1][i]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != y)&&(dis[j-1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if(mapManage->mapModel->Map[j-1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j-1, i);
				}
			}
		}
	}

}
void CalFourth(int x, int y)				//Current�� �������� ��ǥ������ 4��и鿡 ���� ��
{
	int i, j;

	for (i = x; i>dataInterface->robotMovementInterface->robot->rPosition.x; i--)
	{
		for (j = y; j<dataInterface->robotMovementInterface->robot->rPosition.y; j++)
		{
			if ((i != x)&&(dis[j][i+1]>dis[j][i] + 1))			//������ �˻�
			{
				if(mapManage->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i-1]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&(dis[j+1][i]>dis[j][i] + 1))			//���� �˻�
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != y)&&(dis[j-1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if(mapManage->mapModel->Map[j-1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j-1, i);
				}
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