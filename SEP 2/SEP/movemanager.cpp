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
void MoveManager::InitDis()										//dis 초기화
{
	int i, j;

	dis = (int**)malloc((sizeof(int)*mapManager->mapWidth*mapManager->mapHeight));	//	mapWidth, height는 우선 글로벌로 가지고 있다.

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

void MoveManager::CalPath(int x, int y)							//노드에서 목표지점까지의 거리를 계산하는 부분. 방향을 잡는 용도로만 쓰일 듯.
{
	int i=x, j=y;

	if(Map[y][x].data.kind==HAZARD);						//hazard면 계산하지 않음.
	else 
	{
		if ((i != mapManager->mapWidth-1)&&(dis[j][i+1]>dis[j][i] + 1))			//오른쪽 검사
			{
				if (Map[j][i + 1].data.kind == HAZARD);
				else
				{
					dis[j][i+1] = dis[j][i] + 1;
					CalPath(i+1, j);
				}
			}
			if ((i != 0)&&(dis[j][i-1]>dis[j][i] + 1))			//왼쪽 검사
			{
				if (Map[j][i - 1].data.kind == HAZARD);
				else
				{
					dis[j][i-1] = dis[j][i] + 1;
					CalPath(i-1, j);
				}
			}
			if ((j != mapManager->mapHeight-1)&&(dis[j+1][i]>dis[j][i] + 1))			//위쪽 검사
			{
				if(Map[j+1][i].data.kind==HAZARD);
				else
				{
					dis[j+1][i] = dis[j][i] + 1;
					CalPath(i, j+1);
				}
			}
			if ((j != 0)&&(dis[j-1][i]>dis[j][i] + 1))			//아래쪽 검사
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
		return 0;//정상종료
	else
	{
		return POSITIONING_ERROR;
	}
	delete result;
}
int MoveManager::MakeNextMoveData()					//말 그대로 다음 움직임 결정하는 곳
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
void MoveManager::GetNextMoveData()					//움직일 방향으로 로봇을 돌리는 곳
{
	int MData;

	MData=MakeNextMoveData();

	virtualRobot->vDirection = MData;
	dataInterface->robotMovementInterface->RotateRequest(MData);

}

//이거만 따로 있어서 Analyze함수들에서 어떻게 써야할지 모르겠으나 일단 일관성 있게 쓴다.
void MoveManager::GetPositioningSensorData(void *result)//우선 가지고만 있는다.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, rRobot->rPosition, rRobot->rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//여기서 Analyze까지 할지 안할지 모르겠다
}

MoveManager::MoveManager(int** mapInput, Position start,int mapWidth, int mapHeight, MapNode ExP)
{
	InitMoveManager(mapInput, start, mapWidth, mapHeight, ExP);
}

void MoveManager::InitMoveManager(int** mapInput, Position start, int mapWidth, int mapHeight, MapNode ExP)
{
	dataInterface = new DataInterface(start);
	virtualRobot = new VirtualRobot(start);
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);// 2는 처음 바라보는 방향이 2번 방향이라는 뜻
	SetMapModel(mapInput, mapWidth, mapHeight, start);
	RemainSearchSpotList.push_front(ExP);
	rRobot = dataInterface->robotMovementInterface->robot;
	Map = mapManager->mapModel->Map;
}

void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size() > 0)					//모둔 목표지점을 탐사하는 루프
	{
		InitializeMoveData();

		while ((rRobot->rPosition.x != CurrentTarget.position.x) || (rRobot->rPosition.y != CurrentTarget.position.y))				//한 목표지점을 탐사하는 루프
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
			
		
			while (Forward.data.kind == HAZARD)					//앞에 있는 노드가 Hazard가 아닐때까지 회전.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(rRobot->rPosition, rRobot->rDirection);
				AnalyzeHazardSensorData();
			}
			//전에 있던데를 표시함
			RobotMoveRequest();

		}

		RemainSearchSpotList.pop_front();					//탐사가 완료되었으니 리스트에서 제거
		
		for (i = 0; i < mapManager->mapHeight; i++)			//할당받은 메모리 반납
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::RobotMoveRequest()
{
	//이전 위치를 저장
	mapManager->PreviousNode.position.x = rRobot->rPosition.x;
	mapManager->PreviousNode.position.y = rRobot->rPosition.y;
	
	
	//방향 돌리기 추가(PositioningSensor*)
	//실제 로봇 위치 변경
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
			//원래 있을곳으로 감
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
void MoveManager::AnalyzeHazardSensorData()//처리까지함
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