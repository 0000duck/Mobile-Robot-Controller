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
	dis[CurrentTarget.PosY][CurrentTarget.PosX] = 0;
	while(disEnd())
		CalPath(CurrentTarget.PosX, CurrentTarget.PosY);
}
void MoveManager::InitDis()										//dis �ʱ�ȭ
{
	int i, j;

	dis = (int**)malloc((sizeof(int)*mapManager->mapWidth*mapManager->mapHeight));

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

	if(mapManager->mapModel->Map[y][x].data.kind==HAZARD);						//hazard�� ������� ����.
	else 
	{
		if ((i != mapManager->mapWidth-1)&&(dis[j][i+1]>=dis[j][i] + 1))			//������ �˻�
			{
				if (mapManager->mapModel->Map[j][i + 1].data.kind == HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(i+1, j);
				}
			}
			if ((i != 0)&&(dis[j][i-1]>=dis[j][i] + 1))			//���� �˻�
			{
				if (mapManager->mapModel->Map[j][i - 1].data.kind == HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(i-1, j);
				}
			}
			if ((j != mapManager->mapHeight-1)&&(dis[j+1][i]>=dis[j][i] + 1))			//���� �˻�
			{
				if(mapManager->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j+1][i] = dis[j][i] + 1;
					CalPath(i, j+1);
				}
			}
			if ((j != 0)&&(dis[j-1][i]>=dis[j][i] + 1))			//�Ʒ��� �˻�
			{
				if (mapManager->mapModel->Map[j - 1][i].data.kind == HAZARD);
				else					{
					dis[j-1][i] = dis[j][i] + 1;
					CalPath(i, j-1);
				}
			}
	}
}
int MoveManager::disEnd()					//dis�� ��� ���ƴ��� Ȯ��
{
	int i, j;
	
	for(i=0; i<mapManager->mapWidth; i++)
	{
		for(j=0; j<mapManager->mapHeight; j++)
		{
			if(mapManager->mapModel->Map[j][i].data.kind==HAZARD)
				continue;
			if(dis[j][i]==UNKNOWN)
				return 1;
		}
	}

	return 0;
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
	robotPos = *CP;
	if ( CP->x== virtualRobot->vPosition.x &&CP->y == virtualRobot->vPosition.y)
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

	val = dis[robotPos.y][robotPos.x];
	while (true)
	{
		if (val == dis[robotPos.y + 1][robotPos.x] + 1)
			return 8;
		else if (val == dis[robotPos.y][robotPos.x + 1] + 1)
			return 6;
		else if ((robotPos.y>0)&&(val == dis[robotPos.y - 1][robotPos.x] + 1))
			return 2;
		else if ((robotPos.x>0)&&(val == dis[robotPos.y][robotPos.x - 1] + 1))
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
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput, Position start,int mapWidth, int mapHeight, MapNode ExP)
{
	InitMoveManager(mapInput, start, mapWidth, mapHeight, ExP);
}

void MoveManager::InitMoveManager(int** mapInput, Position start, int mapWidth, int mapHeight, MapNode ExP)
{
	robotPos = start;
	dataInterface = new DataInterface(start);
	virtualRobot = new VirtualRobot(start);
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);// 2�� ó�� �ٶ󺸴� ������ 2�� �����̶�� ��
	SetMapModel(mapInput, mapWidth, mapHeight, start);
	RemainSearchSpotList.push_front(ExP);
}

void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size() > 0)					//��� ��ǥ������ Ž���ϴ� ����
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
	mapManager->PreviousNode.PosX = robotPos.x;
	mapManager->PreviousNode.PosY = robotPos.y;
	/*
	switch (dataInterface->robotMovementInterface->robot->rDirection)
	{
	case 8:
		robotPos.x++;
		break;
	case 6:
		robotPos.x++;
		break;
	case 2:
		robotPos.y--;
		break;
	case 4:
		robotPos.x--;
		break;
	}
	*/
	
	//���� ������ �߰�
	dataInterface->robotMovementInterface->MoveRequest();
	virtualRobot->VirtualMove();
	
}

void MoveManager::SetMapModel(int** mapInput, int mapWidth, int mapHeight, Position start)
{

	mapManager = new MapManager(mapInput, mapWidth, mapHeight, start);

}

void MoveManager::AnalyzePositioningSensorData()
{
	int rot = 0;
	int tx = mapManager->PreviousNode.PosX, ty = mapManager->PreviousNode.PosY;
	robotPos = dataInterface->robotMovementInterface->robot->rPosition;
	if (CompareCurrentPos() != 0)
	{
		//���� ���������� ��
		if (tx == robotPos.x){
			if (ty > robotPos.y)
			{
				rot = 2;

			}
			else
			{
				rot = 8;
			}
		}
		else if (tx > robotPos.x)
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
void MoveManager::AnalyzeHazardSensorData()//ó��������
{
	void *result = new void*;
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);
	mapManager->AddHazardPoint(*(int*)result, robotPos);
	delete result;
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result = new void*;
	dataInterface->UseColorSensor(result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition);
	mapManager->AddColorBlob(*(int*)result, robotPos);
	delete result;
}