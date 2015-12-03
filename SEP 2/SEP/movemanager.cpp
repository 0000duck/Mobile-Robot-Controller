#include"moveManager.h"
#include"global.h"
#include"satellite.h"
#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
	CalPath(CurrentPosition.x, CurrentPosition.y);

}
void MoveManager::InitDis()										//dis 초기화
{
	int i, j;

	dis = (int**)malloc((sizeof(int)*mapManager->mapWidth*mapManager->mapHeight));	//	mapWidth, height는 우선 글로벌로 가지고 있다.

	for (i = 0; i < mapManager->mapHeight; i++)
	{
		dis[i] = (int*)malloc((sizeof(int)*mapManager->mapWidth));
	}
	
	for(i=1; i<mapManager->mapWidth; i++)
	{
		for(j=1; j<mapManager->mapHeight; j++)
			dis[i][j]=UNKNOWN;
	}

	CurrentTarget = RemainSearchSpotList.front;

}

void MoveManager::CalPath(int x, int y)							//노드에서 목표지점까지의 거리를 계산하는 부분. 방향을 잡는 용도로만 쓰일 듯.
{
	int i, j;

	if (mapManager->mapModel.Map[x][y].data.kind == HAZARD);						//hazard면 계산하지 않음.
	else if((CurrentTarget.PosX<x)&&(CurrentTarget.PosY<y))						//x, y를 기준으로 목표지점이 3사분면에 있을 때
		CalThird(x, y);
	else if ((CurrentTarget.PosX<x) && (CurrentTarget.PosY>y))					//x, y를 기준으로 목표지점이 2사분면에 있을 때
		CalSecond(x, y);
	else if ((CurrentTarget.PosX>x) && (CurrentTarget.PosY<y))					//x, y를 기준으로 목표지점이 4사분면에 있을 때
		CalFourth(x, y);
	else if ((CurrentTarget.PosX>x) && (CurrentTarget.PosY > y))				//x, y를 기준으로 목표지점이 1사분면에 있을 때
		CalFirst(x, y);
	else if(x==CurrentTarget.PosX)								//x, y가 목표지점과 x축으로 일직선상에 놓여있을 때
	{
		if(y>CurrentTarget.PosY)					//x, y를 기준으로 목표지점이 아래에 있을 때
		{
			for(j=y; j>CurrentTarget.PosY; j--)
				dis[x][j-1]=dis[x][j]+1;
		}
		else										//x, y를 기준으로 목표지점이 위에 있을 때
		{
			for(j=y; j<CurrentTarget.PosY; j++)
				dis[x][j+1]=dis[x][j]+1;
		}
	}
	else if(y==CurrentTarget.PosY)								//x, y가 목표지점과 y축으로 일직선상에 놓여있을 때
	{
		if(x>CurrentTarget.PosX)					//x, y를 기준으로 목표지점이 왼쪽에 있을 때
		{
			for(i=x; i>CurrentTarget.PosX; i--)
				dis[i-1][y]=dis[i][y]+1;
		}
		else										//x, y를 기준으로 목표지점이 오른쪽에 있을 때
		{
			for(i=x; i<CurrentTarget.PosX; i++)
				dis[i+1][y]=dis[i][y]+1;
		}
	}

}
void MoveManager::CalFirst(int x, int y)				//x, y를 기준으로 목표지점이 1사분면에 있을 때
{
	int i, j;

	for (i = CurrentTarget.PosX; i>x; i--)
	{
		for (j = CurrentTarget.PosY; j>y; j--)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//시작점인 경우
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1) && (i != CurrentTarget.PosX))			//오른쪽 검사
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1) && (i != x))			//왼쪽 검사
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1) && (j != CurrentTarget.PosY))			//위쪽 검사
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1) && (j != y))			//밑쪽 검사
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
			}
		}
	}
}
void MoveManager::CalSecond(int x, int y)				//x, y를 기준으로 목표지점이 2사분면에 있을 때
{
	int i, j;

	for (i = CurrentTarget.PosX; i<x; i++)
	{
		for (j = CurrentTarget.PosY; j>y; j--)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//시작점인 경우
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1) && (i != x))			//오른쪽 검사
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1) && (i != CurrentTarget.PosX))			//왼쪽 검사
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1) && (j != CurrentTarget.PosY))			//위쪽 검사
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1) && (j != y))			//밑쪽 검사
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
			}
		}
	}
}
void MoveManager::CalThird(int x, int y)				//x, y를 기준으로 목표지점이 3사분면에 있을 때 
{
	int i, j;

	for (i = CurrentTarget.PosX; i<x; i++)
	{
		for (j = CurrentTarget.PosY; j<y; j++)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//시작점인 경우
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1)&&(i!=x))			//오른쪽 검사
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1)&&(i!=CurrentTarget.PosX))			//왼쪽 검사
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1)&&(j!=y))			//위쪽 검사
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1)&&(j!=CurrentTarget.PosY))			//밑쪽 검사
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
			}
		}
	}

}
void MoveManager::CalFourth(int x, int y)				//x, y를 기준으로 목표지점이 4사분면에 있을 때
{
	int i, j;

	for (i = CurrentTarget.PosX; i>x; i--)
	{
		for (j = CurrentTarget.PosY; j<y; j++)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//시작점인 경우
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1) && (i != CurrentTarget.PosX))			//오른쪽 검사
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1) && (i != x))			//왼쪽 검사
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1) && (j != y))			//위쪽 검사
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1) && (j != CurrentTarget.PosY))			//밑쪽 검사
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
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

	if ( CP->x== virtualRobot->CurrentPosition.x &&CP->y == virtualRobot->CurrentPosition.y)
		return 0;//정상종료
	else
	{
		return POSITIONING_ERROR;
	}
}
int MoveManager::MakeNextMoveData()					//말 그대로 다음 움직임 결정하는 곳
{
	int val, dir;

	val = dis[CurrentPosition.x][CurrentPosition.y];
	while (true)
	{
		if (val == dis[CurrentPosition.x][CurrentPosition.y + 1] + 1)
			dir=8;
		else if (val == dis[CurrentPosition.x + 1][CurrentPosition.y] + 1)
			dir=6;
		else if (val == dis[CurrentPosition.x][CurrentPosition.y - 1] + 1)
			dir=2;
		else if (val == dis[CurrentPosition.x - 1][CurrentPosition.y] + 1)
			dir=4;
		else
			val++;
	}



}
void MoveManager::GetNextMoveData()					//움직일 방향으로 로봇을 돌리는 곳
{
	int MData;

	MData=MakeNextMoveData();
	virtualRobot->CurrentDirection = MData;

	dataInterface->robotMovementInterface->MoveRequest(MData);


}

//이거만 따로 있어서 Analyze함수들에서 어떻게 써야할지 모르겠으나 일단 일관성 있게 쓴다.
void MoveManager::GetPositioningSensorData(void *result)//우선 가지고만 있는다.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot.rPosition, dataInterface->robotMovementInterface->robot.rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//여기서 Analyze까지 할지 안할지 모르겠다
}

MoveManager::MoveManager(int** mapInput, Position start)
{
	dataInterface = new DataInterface();
	virtualRobot = new VirtualRobot(start);
	SetMapModel(mapInput,mapWidth, mapHeight, start);
	//SetMapModel(mapInput);
	virtualRobot = new VirtualRobot(start);	//생성자호출
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);
}



void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size > 0)					//모둔 목표지점을 탐사하는 루프
	{
		InitializeMoveData();

		while ((CurrentPosition.x!=CurrentTarget.PosX)||(CurrentPosition.y!=CurrentTarget.PosY))				//한 목표지점을 탐사하는 루프
		{
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();.
			Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot-CurrentDirection);
			
		
			while (Forward.data.kind == HAZARD)					//앞에 있는 노드가 Hazard가 아닐때까지 회전.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot.robotPosition, dataInterface->robotMovementInterface->robot.CurrentDirection);
				AnalyzeHazardSensorData();
			}

			dataInterface->robotMovementInterface->robot.Move();//실제 로봇 move
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
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot.rPosition, dataInterface->robotMovementInterface->robot.rDirection);
	mapManager->AddHazardPoint(*(int*)result);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface->UseColorSensor(result, mapManager->mapModel, dataInterface->robotMovementInterface->robot.rPosition, dataInterface->robotMovementInterface->robot.rDirection);
	mapManager->AddColorBlob(*(int*)result);
}