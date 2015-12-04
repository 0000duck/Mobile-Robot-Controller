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
void MoveManager::InitDis()										//dis 초기화
{
	int i, j;

	dis = (int**)malloc((sizeof(int)*mapManager->mapWidth*mapManager->mapHeight));	//	mapWidth, height는 우선 글로벌로 가지고 있다.

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

void CalPath(int x, int y)							//노드에서 목표지점까지의 거리를 계산하는 부분. 방향을 잡는 용도로만 쓰일 듯.
{
	int i, j;

	if(mapManager->mapModel->Map[x][y].data.kind==HAZARD);						//hazard면 계산하지 않음.
	else if((dataInterface->robotMovementInterface->robot->rPosition.x>x)&&(dataInterface->robotMovementInterface->robot->rPosition.y>y))						//Current를 기준으로 x, y이 3사분면에 있을 때
		CalThird(x, y);
	else if ((dataInterface->robotMovementInterface->robot->rPosition.x<x) && (dataInterface->robotMovementInterface->robot->rPosition.y>y))					//Current를 기준으로 x, y이 2사분면에 있을 때
		CalSecond(x, y);
	else if ((dataInterface->robotMovementInterface->robot->rPosition.x>x) && (dataInterface->robotMovementInterface->robot->rPosition.y<y))					//Current를 기준으로 x, y이 4사분면에 있을 때
		CalFourth(x, y);
	else if ((dataInterface->robotMovementInterface->robot->rPosition.x<x) && (dataInterface->robotMovementInterface->robot->rPosition.y < y))				//Current를 기준으로 x, y이 1사분면에 있을 때
		CalFirst(x, y);
	else if(x==dataInterface->robotMovementInterface->robot->rPosition.x)								//Current가 x, y과 x축으로 일직선상에 놓여있을 때
	{
		if(y<dataInterface->robotMovementInterface->robot->rPosition.y)					//Current를 기준으로 x, y이 아래쪽에 있을 때
		{
			for(j=y; j<dataInterface->robotMovementInterface->robot->rPosition.y; j++)
			{
				if(mapManager->mapModel->Map[j+1][x].data.kind==HAZARD);
				else if(dis[j+1][x]>dis[j][x]+1)
					dis[j+1][x]=dis[j][x]+1;
			}
		}
		else										//Current를 기준으로 x, y이 위쪽에 있을 때
		{
			for(j=y; j>dataInterface->robotMovementInterface->robot->rPosition.y; j--)
			{
				if(mapManager->mapModel->Map[j-1][x].data.kind==HAZARD);
				else if(dis[j-1][x]>dis[j][x]+1)
					dis[j-1][x]=dis[j][x]+1;
			}
		}
	}
	else if(y==dataInterface->robotMovementInterface->robot->rPosition.y)								//Current가 x, y과 y축으로 일직선상에 놓여있을 때
	{
		if(x<dataInterface->robotMovementInterface->robot->rPosition.x)					//Current를 기준으로 x, y이 왼쪽에 있을 때
		{
			for(i=x; i<dataInterface->robotMovementInterface->robot->rPosition.x; i++)
			{
				if(mapManager->mapModel->Map[y][i+1].data.kind==HAZARD);
				else if(dis[y][i+1]>dis[y][i]+1)
					dis[y][i+1]=dis[y][i]+1;
			}
		}
		else										//Current를 기준으로 x, y이 오른쪽에 있을 때
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
void CalFirst(int x, int y)				//Current를 기준으로 목표지점이 1사분면에 있을 때
{
	int i, j;

	for (i = x; i>dataInterface->robotMovementInterface->robot->rPosition.x; i--)
	{
		for (j = y; j>dataInterface->robotMovementInterface->robot->rPosition.y; j--)
		{
			if ((i != x)&&(dis[j][i+1]>dis[j][i] + 1))			//오른쪽 검사
			{
				if(mapManager->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i-1]>dis[j][i] + 1))			//왼쪽 검사
			{
				if(mapManager->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != y)&(dis[j+1][i]>dis[j][i] + 1))			//위쪽 검사
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&&(dis[j-1][i]>dis[j][i] + 1))			//아래쪽 검사
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
void CalSecond(int x, int y)				//Current를 기준으로 목표지점이 2사분면에 있을 때
{
	int i, j;

	for (i = x; i<dataInterface->robotMovementInterface->robot->rPosition.x; i++)
	{
		for (j = y; j>dataInterface->robotMovementInterface->robot->rPosition.y; j--)
		{
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i+1]>dis[j][i] + 1))			//오른쪽 검사
			{
				if(mapManage->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != x)&&(dis[j][i-1]>dis[j][i] + 1))			//왼쪽 검사
			{
				if(mapManage->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != y)&(dis[j+1][i]>dis[j][i] + 1))			//위쪽 검사
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&&(dis[j-1][i]>dis[j][i] + 1))			//아래쪽 검사
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
void CalThird(int x, int y)				//Current를 기준으로 목표지점이 3사분면에 있을 때 
{
	int i, j;

	for (i = x; i<dataInterface->robotMovementInterface->robot->rPosition.x; i++)
	{
		for (j = y; j<dataInterface->robotMovementInterface->robot->rPosition.y; j++)
		{
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i+1]>dis[j][i] + 1))			//오른쪽 검사
			{
				if(mapManage->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != x)&&(dis[j][i-1]>dis[j][i] + 1))			//왼쪽 검사
			{
				if(mapManage->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&(dis[j+1][i]>dis[j][i] + 1))			//위쪽 검사
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != y)&&(dis[j-1][i]>dis[j][i] + 1))			//아래쪽 검사
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
void CalFourth(int x, int y)				//Current를 기준으로 목표지점이 4사분면에 있을 때
{
	int i, j;

	for (i = x; i>dataInterface->robotMovementInterface->robot->rPosition.x; i--)
	{
		for (j = y; j<dataInterface->robotMovementInterface->robot->rPosition.y; j++)
		{
			if ((i != x)&&(dis[j][i+1]>dis[j][i] + 1))			//오른쪽 검사
			{
				if(mapManage->mapModel->Map[j][i+1].data.kind==HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(j, i+1);
				}
			}
			if ((i != dataInterface->robotMovementInterface->robot->rPosition.x)&&(dis[j][i-1]>dis[j][i] + 1))			//왼쪽 검사
			{
				if(mapManage->mapModel->Map[j][i-1].data.kind==HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(j, i-1);
				}
			}
			if ((j != dataInterface->robotMovementInterface->robot->rPosition.y)&(dis[j+1][i]>dis[j][i] + 1))			//위쪽 검사
			{
				if(mapManage->mapModel->Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j][i] = dis[j][i] + 1;
					CalPath(j+1, i);
				}
			}
			if ((j != y)&&(dis[j-1][i]>dis[j][i] + 1))			//아래쪽 검사
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
		return 0;//정상종료
	else
	{
		return POSITIONING_ERROR;
	}
}
int MoveManager::MakeNextMoveData()					//말 그대로 다음 움직임 결정하는 곳
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
void MoveManager::GetNextMoveData()					//움직일 방향으로 로봇을 돌리는 곳
{
	int MData;

	MData=MakeNextMoveData();
	virtualRobot->vDirection = MData;

	dataInterface->robotMovementInterface->MoveRequest(MData);


}

//이거만 따로 있어서 Analyze함수들에서 어떻게 써야할지 모르겠으나 일단 일관성 있게 쓴다.
void MoveManager::GetPositioningSensorData(void *result)//우선 가지고만 있는다.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//여기서 Analyze까지 할지 안할지 모르겠다
}

MoveManager::MoveManager(int** mapInput, Position start)
{
	robotPos = start;
	dataInterface = new DataInterface();
	virtualRobot = new VirtualRobot(start);
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);// 2는 처음 바라보는 방향이 2번 방향이라는 뜻
	
	SetMapModel(mapInput,mapWidth, mapHeight, start);
}



void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size > 0)					//모둔 목표지점을 탐사하는 루프
	{
		InitializeMoveData();

		while ((robotPos.x != CurrentTarget.PosX) || (robotPos.y != CurrentTarget.PosY))				//한 목표지점을 탐사하는 루프
		{
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);
			
		
			while (Forward.data.kind == HAZARD)					//앞에 있는 노드가 Hazard가 아닐때까지 회전.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot->rDirection);
				AnalyzeHazardSensorData();
			}

			dataInterface->robotMovementInterface->robot->Move();//실제 로봇 move
			virtualRobot->VirtualMove();

		}

		RemainSearchSpotList.pop_front();					//탐사가 완료되었으니 리스트에서 제거
		
		for (i = 0; i < mapManager->mapHeight; i++)			//할당받은 메모리 반납
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
		//원래 있을곳으로 감
	}
}
void MoveManager::AnalyzeHazardSensorData()//처리까지함
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