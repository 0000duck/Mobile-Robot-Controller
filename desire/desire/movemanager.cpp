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
MoveManager* MoveManager::pInstance = NULL;

void MoveManager::InitializeMoveData()
{
	InitDis();
	dis[CurrentTarget.position.y][CurrentTarget.position.x] = 0;
	while (DisEnd())
		CalPath(CurrentTarget.position.x, CurrentTarget.position.y);
}
void MoveManager::InitDis()										//dis 초기화
{
	int i, j;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();

	dis = (int**)malloc((sizeof(int)*mapWidth*mapHeight));	//	mapWidth, height는 우선 글로벌로 가지고 있다.

	for (i = 0; i < mapHeight; i++)
	{
		dis[i] = (int*)malloc((sizeof(int)*mapWidth));
	}
	
	for (j = 0; j < mapHeight; j++)
	{
		for (i = 0; i<mapWidth; i++)
			dis[j][i]=UNKNOWN;
	}

}

void MoveManager::CalPath(int x, int y)							//노드에서 목표지점까지의 거리를 계산하는 부분. 방향을 잡는 용도로만 쓰일 듯.
{
	int i=x, j=y;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	if(Map[y][x].data.kind==HAZARD);						//hazard면 계산하지 않음.
	else 
	{
		if ((i != mapWidth - 1) && (dis[j][i + 1]>dis[j][i] + 1))			//오른쪽 검사
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
			if ((j != mapHeight- 1) && (dis[j + 1][i]>dis[j][i] + 1))			//위쪽 검사
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
int MoveManager::DisEnd()					//dis가 모두 계산됐는지 확인
{
	int i, j;
	int width = mapManager->getMapWidth(), height = mapManager->getMapHeight();

	for (i = 0; i<width; i++)
	{
		for (j = 0; j<height; j++)
		{
			if (Map[j][i].data.kind == HAZARD)
				continue;
			if (dis[j][i] == UNKNOWN)
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

	if ( (CP->x== virtualRobot->getvPosition().x )&&(CP->y == virtualRobot->getvPosition().y))
		return 0;//정상종료
	else
	{
		return POSITIONING_ERROR;
	}
	delete result;
}
int MoveManager::MakeNextMoveData()					//말 그대로 다음 움직임 결정하는 곳
{
	int val, tmp;
	int robotx = dataInterface->getRobotPosition().x;
	int	roboty = dataInterface->getRobotPosition().y;
	int mapWidth = mapModel->getMapWidth();
	int mapHeight = mapModel->getMapHeight();
	tmp = val = dis[roboty][robotx];
	while (true)
	{
		if ((roboty<mapHeight-1)&&(val == dis[roboty + 1][robotx] + 1) && (Map[roboty + 1][robotx].data.kind != HAZARD))
			return 2;
		else if ((robotx<mapWidth-1)&&(val == dis[roboty][robotx + 1] + 1) && (Map[roboty][robotx+1].data.kind != HAZARD))
			return 6;
		else if ((roboty>0) && (val == dis[roboty - 1][robotx] + 1) && (Map[roboty - 1][robotx].data.kind != HAZARD))
			return 8;
		else if ((robotx>0) && (val == dis[roboty][robotx - 1] + 1) && (Map[roboty][robotx-1].data.kind != HAZARD))
			return 4;
		else
			val++;
	}



}
void MoveManager::GetNextMoveData()					//움직일 방향으로 로봇을 돌리는 곳
{
	int MData;

	MData=MakeNextMoveData();

	if (MData == -1)
		return;
	virtualRobot->virtualRotate(MData);
	dataInterface->requestRobotRotate(MData);

}

//이거만 따로 있어서 Analyze함수들에서 어떻게 써야할지 모르겠으나 일단 일관성 있게 쓴다.
void MoveManager::GetPositioningSensorData(void *result)//우선 가지고만 있는다.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapModel, dataInterface->getRobotPosition(), dataInterface->getRobotDirection());

	//AnalyzePositioningSensorData(*(Position *)result);//여기서 Analyze까지 할지 안할지 모르겠다
}

MoveManager::MoveManager()
{
	isInit = false;
}

void MoveManager::InitMoveManager(int startY, int startX, int mapHeight, int mapWidth)
{
	if (isInit == true) return;
	Position start;
	start.x = startX;
	start.y = startY;
	MapNode m, n, k, l;
	m.position.x = 0;
	m.position.y = 0;
	n.position.x = 19;
	n.position.y = 7;
	k.position.x = 0;
	k.position.y = 2;
	l.position.x = 9;
	l.position.y = 13;
	dataInterface = new DataInterface(start, 2);
	virtualRobot = new VirtualRobot(start, 2);;// 2는 처음 바라보는 방향이 2번 방향이라는 뜻
	SetMapModel(mapWidth, mapHeight, start);

	RemainSearchSpotList.push_front(n);
	RemainSearchSpotList.push_front(m);
	RemainSearchSpotList.push_front(k);
	RemainSearchSpotList.push_front(l);
	mapModel = mapManager->getMapModel();
	Map = mapModel->getMapNode();
}

int MoveManager::generator(){
	return ran.get();
}

void MoveManager::Explore()
{
	MapNode Forward;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	int i;

	while(RemainSearchSpotList.size() > 0)					//모둔 목표지점을 탐사하는 루프
	{
		CurrentTarget = RemainSearchSpotList.front();
		Map[CurrentTarget.position.y][CurrentTarget.position.x].data.kind = EXPLROATIONPOINT;
		if (Map[CurrentTarget.position.y][CurrentTarget.position.x].data.kind == HAZARD)
		{
			printf("can't explore\n");
			RemainSearchSpotList.pop_front();
			continue;
		}

		InitializeMoveData();

		while ((dataInterface->getRobotPosition().x != CurrentTarget.position.x) || (dataInterface->getRobotPosition().y != CurrentTarget.position.y))				//한 목표지점을 탐사하는 루프
		{

		
			
			for (int j = 0; j < mapHeight; j++)
			{
				for (int k = 0; k < mapWidth; k++)
				{
					if (k == dataInterface->getRobotPosition().x && j == dataInterface->getRobotPosition().y)
						printf("R ");
					else if (k == CurrentTarget.position.x && j == CurrentTarget.position.y)
					{
						printf("+ ");
					}
					else if (Map[j][k].data.kind == NORMAL)
					{
						printf("- ");
					}
					else if (Map[j][k].data.kind == HAZARD)
					{
						printf("H ");
					}
				}
				printf("\n");
			}
			
			if (Map[CurrentTarget.position.y][CurrentTarget.position.x].data.kind == HAZARD)
			{
				printf("can't explore\n");
				RemainSearchSpotList.pop_front();
				continue;
			}
			mapManager->SearchDis();

			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
		
		
			while (Forward.data.kind == HAZARD)					//앞에 있는 노드가 Hazard가 아닐때까지 회전.
			{
				mapManager->SearchDis();
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
				AnalyzeHazardSensorData();
			}
			//전에 있던데를 표시함
			RobotMoveRequest();
			possibleError();// 재수없으면 한번 더간다(수정하는 거에선 안감)
			printf(" (%d,%d) \n", dataInterface->getRobotPosition().y, dataInterface->getRobotPosition().x);


		}
		printf(" 탐사 완료 현위치 : (%d,%d) \n", dataInterface->getRobotPosition().y, dataInterface->getRobotPosition().x);

		RemainSearchSpotList.pop_front();					//탐사가 완료되었으니 리스트에서 제거
		
		for (i = 0; i < mapHeight; i++)			//할당받은 메모리 반납
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::RobotMoveRequest()
{
	//이전 위치를 저장
	mapManager->setPreviousNode(dataInterface->getRobotPosition());
	//방향 돌리기 추가(PositioningSensor*)
	//실제 로봇 위치 변경
	dataInterface->requestRobotMove();
	setPositioningSensor();
	virtualRobot->VirtualMove();
	
}

void MoveManager::SetMapModel(int mapWidth, int mapHeight, Position start)
{

	mapManager = new MapManager(mapWidth, mapHeight, start);

}

void MoveManager::AnalyzePositioningSensorData()
{
	if (CompareCurrentPos() == POSITIONING_ERROR){
		int rot = 0;
		int tx = mapManager->getPreviousNode().position.x, ty = mapManager->getPreviousNode().position.y;
		if (CompareCurrentPos() != 0)
		{
			//원래 있을곳으로 감
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
			dataInterface->requestRobotMove();
			setPositioningSensor();

			printf("error fix %d %d\n", dataInterface->getRobotPosition().y, dataInterface->getRobotPosition().x);

			

		}
	}
}
void MoveManager::AnalyzeHazardSensorData()//처리까지함
{
	void *result = new void*;
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapModel, dataInterface->getRobotPosition(), dataInterface->getRobotDirection());

	if (*(int*)result & 0x1000)
	{
		printf("8 ");
	}
	if (*(int*)result & 0x0100)
	{
		printf("4 ");
	}
	if (*(int*)result & 0x0010)
	{
		printf("2 ");
	}
	if (*(int*)result & 0x0001)
	{
		printf("6 ");
	}
	if (*(int*)result > 0){
		printf("hazard added\n");
	
	}
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

void MoveManager::possibleError()
{
	MapNode Forward;
	if ((generator()<10) && (dataInterface->getRobotPosition().x > 0) && (dataInterface->getRobotPosition().y > 0) && (dataInterface->getRobotPosition().x<mapManager->getMapWidth()) && (dataInterface->getRobotPosition().y<mapManager->getMapHeight())){
	
		Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
		if (Forward.data.kind != HAZARD){
			printf("error 발생 2칸 이동\n");
			dataInterface->requestRobotMove();
			setPositioningSensor();
			}
	}
	
}