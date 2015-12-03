#include"moveManager.h"
#include"global.h"

#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
	CalPath(CurrentPosition.x, CurrentPosition.y);
	
}
void InitDis()										//dis 초기화
{
	int i, j;

	dis = (int**)malloc((sizeof(int)*mapWidth*mapHeight));

	for (i = 0; i <mapHeight; i++)
	{
		dis[i] = (int*)malloc((sizeof(int)*mapWidth));
	}
	
	for(i=0; i<mapWidth; i++)
	{
		for(j=0; j<mapHeight; j++)
			dis[i][j]=UNKNOWN;
	}

}

void CalPath(int x, int y)							//노드에서 목표지점까지의 거리를 계산하는 부분. 방향을 잡는 용도로만 쓰일 듯.
{
	int i, j;

	if(mapManager.mapModel.Map[x][y].kind==HAZARD);						//hazard면 계산하지 않음.
	else if((Current.PosX>x)&&(Current.PosY>y))						//Current를 기준으로 x, y이 3사분면에 있을 때
		CalThird(x, y);
	else if ((Current.PosX>x) && (Current.PosY<y))					//Current를 기준으로 x, y이 2사분면에 있을 때
		CalSecond(x, y);
	else if ((Current.PosX<x) && (Current.PosY>y))					//Current를 기준으로 x, y이 4사분면에 있을 때
		CalFourth(x, y);
	else if ((Current.PosX<x) && (Current.PosY < y))				//Current를 기준으로 x, y이 1사분면에 있을 때
		CalFirst(x, y);
	else if(x==Current.PosX)								//Current가 x, y과 x축으로 일직선상에 놓여있을 때
	{
		if(y<Current.PosY)					//Current를 기준으로 x, y이 왼쪽에 있을 때
		{
			for(j=y; j<Current.PosY; j++)
			{
				if(Map[x][j+1].kind==HAZARD);
				else if(dis[x][j+1]>dis[x][j]+1)
					dis[x][j+1]=dis[x][j]+1;
			}
		}
		else										//Current를 기준으로 x, y이 오른쪽에 있을 때
		{
			for(j=y; j>Current.PosY; j--)
			{
				if(Map[x][j-1].kind==HAZARD);
				else if(dis[x][j-1]>dis[x][j]+1)
					dis[x][j-1]=dis[x][j]+1;
			}
		}
	}
	else if(y==Current.PosY)								//Current가 x, y과 y축으로 일직선상에 놓여있을 때
	{
		if(x<Current.PosX)					//Current를 기준으로 x, y이 위쪽에 있을 때
		{
			for(i=x; i<Current.PosX; i++)
			{
				if(Map[i+1][y].kind==HAZARD);
				else if(dis[i+1][y]>dis[i][y]+1)
					dis[i+1][y]=dis[i][y]+1;
			}
		}
		else										//Current를 기준으로 x, y이 아래쪽에 있을 때
		{
			for(i=x; i>Current.PosX; i--)
			{
				if(Map[i-1][y].kind==HAZARD);
				else if(dis[i-1][y]>dis[i][y]+1)
					dis[i-1][y]=dis[i][y]+1;
			}
		}
	}

}
void CalFirst(int x, int y)				//Current를 기준으로 목표지점이 1사분면에 있을 때
{
	int i, j;

	for (i = x; i>Current.PosX; i--)
	{
		for (j = y; j>Current.PosY; j--)
		{
			if ((i != x)&&(dis[i + 1][j]>dis[i][j] + 1))			//아래쪽 검사
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i != Current.PosX)&&(dis[i - 1][j]>dis[i][j] + 1))			//위쪽 검사
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j != y)&(dis[i][j + 1]>dis[i][j] + 1))			//오른쪽 검사
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j != Current.PosY)&&(dis[i][j - 1]>dis[i][j] + 1))			//왼쪽 검사
			{
				if(Map[i][j-1].kind==HAZARD);
				else
				{
					dis[i][j - 1] = dis[i][j] + 1;
					CalPath(i, j - 1);
				}
			}
		}
	}
}
void CalSecond(int x, int y)				//Current를 기준으로 목표지점이 2사분면에 있을 때
{
	int i, j;

	for (i = x; i<Current.PosX; i++)
	{
		for (j = y; j>Current.PosY; j--)
		{
			if ((i != Current.PosX)&&(dis[i + 1][j]>dis[i][j] + 1))			//아래쪽 검사
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i != x)&&(dis[i - 1][j]>dis[i][j] + 1))			//위쪽 검사
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j != y)&&(dis[i][j + 1]>dis[i][j] + 1))			//오른쪽 검사
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j != Current.PosY)&&(dis[i][j - 1]>dis[i][j] + 1))			//왼쪽 검사
			{
				if(Map[i][j-1].kind==HAZARD);
				else
				{
					dis[i][j - 1] = dis[i][j] + 1;
					CalPath(i, j - 1);
				}
			}
		}
	}
}
void CalThird(int x, int y)				//Current를 기준으로 목표지점이 3사분면에 있을 때 
{
	int i, j;

	for (i = x; i<Current.PosX; i++)
	{
		for (j = y; j<Current.PosY; j++)
		{
			if ((i!=Current.PosX)&&(dis[i + 1][j]>dis[i][j] + 1))			//아래쪽 검사
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i!=x)&&(dis[i - 1][j]>dis[i][j] + 1))			//위쪽 검사
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j!=Current.PosY)&&(dis[i][j + 1]>dis[i][j] + 1))			//오른쪽 검사
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j!=y)&&(dis[i][j - 1]>dis[i][j] + 1))			//왼쪽 검사
			{
				if(Map[i][j-1].kind==HAZARD);
				else
				{
					dis[i][j - 1] = dis[i][j] + 1;
					CalPath(i, j - 1);
				}
			}
		}
	}

}
void CalFourth(int x, int y)				//Current를 기준으로 목표지점이 4사분면에 있을 때
{
	int i, j;

	for (i = x; i>Current.PosX; i--)
	{
		for (j = y; j<Current.PosY; j++)
		{
			if ((i != x)&&(dis[i + 1][j]>dis[i][j] + 1))			//아래쪽 검사
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i != Current.PosX)&&(dis[i - 1][j]>dis[i][j] + 1))			//위쪽 검사
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j != Current.PosY)&&(dis[i][j + 1]>dis[i][j] + 1))			//오른쪽 검사
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j != y)&&(dis[i][j - 1]>dis[i][j] + 1))			//왼쪽 검사
			{
				if(Map[i][j-1].kind==HAZARD);
				else
				{
					dis[i][j - 1] = dis[i][j] + 1;
					CalPath(i, j - 1);
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

	if ( CP->x== virtualRobot.CurrentPosition.x &&CP->y == virtualRobot.CurrentPosition.y)
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
	virtualRobot.CurrentDirection = MData;
	dataInterface.robotMovementInterface.robot.Rotate(MData);
	


}

//이거만 따로 있어서 Analyze함수들에서 어떻게 써야할지 모르겠으나 일단 일관성 있게 쓴다.
void MoveManager::GetPositioningSensorData(void *result)//우선 가지고만 있는다.
{
	dataInterface.UseSensor(POSITIONING_SENSOR, result);

	//AnalyzePositioningSensorData(*(Position *)result);//여기서 Analyze까지 할지 안할지 모르겠다
}

MoveManager::MoveManager(int** mapInput, Position start)
{
	SetMapModel(mapInput);
	dataInterface.robotMovementInterface.robot.robotPosition.x = start.x;//나중에 함수로 바꿈
	dataInterface.robotMovementInterface.robot.robotPosition.y = start.y;
	virtualRobot(start);	//생성자호출
}

void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size() > 0)					//모둔 목표지점을 탐사하는 루프
	{
		InitializeMoveData();

		while ((CurrentPosition.x!=CurrentTarget.PosX)||(CurrentPosition.y!=CurrentTarget.PosY))				//한 목표지점을 탐사하는 루프
		{
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager.GetForwardMapNode(dataInterface.robotMovementInterface.robot.robotPosition, dataInterface.robotMovementInterface.robot.CurrentDirection);
			
			while (Forward.data.kind == HAZARD)					//앞에 있는 노드가 Hazard가 아닐때까지 회전.
			{
				GetNextMoveData();
				Forward = mapManager.GetForwardMapNode(dataInterface.robotMovementInterface.robot.robotPosition, dataInterface.robotMovementInterface.robot.CurrentDirection);
				AnalyzeHazardSensorData();
			}

			dataInterface.robotMovementInterface.robot.Move();//실제 로봇 move
			virtualRobot.VirtualMove();

		}

		RemainSearchSpotList.pop_front();					//탐사가 완료되었으니 리스트에서 제거
		
		for (i = 0; i < mapManager.mapHeight; i++)			//할당받은 메모리 반납
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::SetMapModel(int** mapInput)
{
	mapManager(mapInput);
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
	dataInterface.UseSensor(HAZARD_SENSOR, result);//현재는 4방향 다 받아오므로 그와 맞게 함수를 짬
	mapManager.AddHazardPoint(*(int*)result);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface.UseColorSensor(result);
	mapManager.AddColorBlob(*(int*)result);
}