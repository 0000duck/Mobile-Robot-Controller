#include"moveManager.h"
#include"global.h"
#include"satellite.h"
#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
	CalPath(CurrentPosition.x, CurrentPosition.y);

}
void MoveManager::InitDis()										//dis �ʱ�ȭ
{
	int i, j;

	dis = (int**)malloc((sizeof(int)*mapManager->mapWidth*mapManager->mapHeight));	//	mapWidth, height�� �켱 �۷ι��� ������ �ִ�.

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

void MoveManager::CalPath(int x, int y)							//��忡�� ��ǥ���������� �Ÿ��� ����ϴ� �κ�. ������ ��� �뵵�θ� ���� ��.
{
	int i, j;

	if (mapManager->mapModel.Map[x][y].data.kind == HAZARD);						//hazard�� ������� ����.
	else if((CurrentTarget.PosX<x)&&(CurrentTarget.PosY<y))						//x, y�� �������� ��ǥ������ 3��и鿡 ���� ��
		CalThird(x, y);
	else if ((CurrentTarget.PosX<x) && (CurrentTarget.PosY>y))					//x, y�� �������� ��ǥ������ 2��и鿡 ���� ��
		CalSecond(x, y);
	else if ((CurrentTarget.PosX>x) && (CurrentTarget.PosY<y))					//x, y�� �������� ��ǥ������ 4��и鿡 ���� ��
		CalFourth(x, y);
	else if ((CurrentTarget.PosX>x) && (CurrentTarget.PosY > y))				//x, y�� �������� ��ǥ������ 1��и鿡 ���� ��
		CalFirst(x, y);
	else if(x==CurrentTarget.PosX)								//x, y�� ��ǥ������ x������ �������� �������� ��
	{
		if(y>CurrentTarget.PosY)					//x, y�� �������� ��ǥ������ �Ʒ��� ���� ��
		{
			for(j=y; j>CurrentTarget.PosY; j--)
				dis[x][j-1]=dis[x][j]+1;
		}
		else										//x, y�� �������� ��ǥ������ ���� ���� ��
		{
			for(j=y; j<CurrentTarget.PosY; j++)
				dis[x][j+1]=dis[x][j]+1;
		}
	}
	else if(y==CurrentTarget.PosY)								//x, y�� ��ǥ������ y������ �������� �������� ��
	{
		if(x>CurrentTarget.PosX)					//x, y�� �������� ��ǥ������ ���ʿ� ���� ��
		{
			for(i=x; i>CurrentTarget.PosX; i--)
				dis[i-1][y]=dis[i][y]+1;
		}
		else										//x, y�� �������� ��ǥ������ �����ʿ� ���� ��
		{
			for(i=x; i<CurrentTarget.PosX; i++)
				dis[i+1][y]=dis[i][y]+1;
		}
	}

}
void MoveManager::CalFirst(int x, int y)				//x, y�� �������� ��ǥ������ 1��и鿡 ���� ��
{
	int i, j;

	for (i = CurrentTarget.PosX; i>x; i--)
	{
		for (j = CurrentTarget.PosY; j>y; j--)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//�������� ���
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1) && (i != CurrentTarget.PosX))			//������ �˻�
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1) && (i != x))			//���� �˻�
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1) && (j != CurrentTarget.PosY))			//���� �˻�
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1) && (j != y))			//���� �˻�
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
			}
		}
	}
}
void MoveManager::CalSecond(int x, int y)				//x, y�� �������� ��ǥ������ 2��и鿡 ���� ��
{
	int i, j;

	for (i = CurrentTarget.PosX; i<x; i++)
	{
		for (j = CurrentTarget.PosY; j>y; j--)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//�������� ���
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1) && (i != x))			//������ �˻�
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1) && (i != CurrentTarget.PosX))			//���� �˻�
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1) && (j != CurrentTarget.PosY))			//���� �˻�
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1) && (j != y))			//���� �˻�
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
			}
		}
	}
}
void MoveManager::CalThird(int x, int y)				//x, y�� �������� ��ǥ������ 3��и鿡 ���� �� 
{
	int i, j;

	for (i = CurrentTarget.PosX; i<x; i++)
	{
		for (j = CurrentTarget.PosY; j<y; j++)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//�������� ���
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1)&&(i!=x))			//������ �˻�
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1)&&(i!=CurrentTarget.PosX))			//���� �˻�
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1)&&(j!=y))			//���� �˻�
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1)&&(j!=CurrentTarget.PosY))			//���� �˻�
			{
				dis[i][j - 1] = dis[i][j] + 1;
				CalPath(i, j - 1);
			}
		}
	}

}
void MoveManager::CalFourth(int x, int y)				//x, y�� �������� ��ǥ������ 4��и鿡 ���� ��
{
	int i, j;

	for (i = CurrentTarget.PosX; i>x; i--)
	{
		for (j = CurrentTarget.PosY; j<y; j++)
		{
			if ((i == CurrentTarget.PosX) && (j == CurrentTarget.PosY))			//�������� ���
				continue;
			if ((dis[i + 1][j]>dis[i][j] + 1) && (i != CurrentTarget.PosX))			//������ �˻�
			{
				dis[i + 1][j] = dis[i][j] + 1;
				CalPath(i + 1, j);
			}
			if ((dis[i - 1][j]>dis[i][j] + 1) && (i != x))			//���� �˻�
			{
				dis[i - 1][j] = dis[i][j] + 1;
				CalPath(i - 1, j);
			}
			if ((dis[i][j + 1]>dis[i][j] + 1) && (j != y))			//���� �˻�
			{
				dis[i][j + 1] = dis[i][j] + 1;
				CalPath(i, j + 1);
			}
			if ((dis[i][j - 1]>dis[i][j] + 1) && (j != CurrentTarget.PosY))			//���� �˻�
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
		return 0;//��������
	else
	{
		return POSITIONING_ERROR;
	}
}
int MoveManager::MakeNextMoveData()					//�� �״�� ���� ������ �����ϴ� ��
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
void MoveManager::GetNextMoveData()					//������ �������� �κ��� ������ ��
{
	int MData;

	MData=MakeNextMoveData();
	virtualRobot->CurrentDirection = MData;

	dataInterface->robotMovementInterface->MoveRequest(MData);


}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot.rPosition, dataInterface->robotMovementInterface->robot.rDirection);

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput, Position start)
{
	dataInterface = new DataInterface();
	virtualRobot = new VirtualRobot(start);
	SetMapModel(mapInput,mapWidth, mapHeight, start);
	//SetMapModel(mapInput);
	virtualRobot = new VirtualRobot(start);	//������ȣ��
	dataInterface->robotMovementInterface->robot = new Robot(start, 2);
}



void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size > 0)					//��� ��ǥ������ Ž���ϴ� ����
	{
		InitializeMoveData();

		while ((CurrentPosition.x!=CurrentTarget.PosX)||(CurrentPosition.y!=CurrentTarget.PosY))				//�� ��ǥ������ Ž���ϴ� ����
		{
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();.
			Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot->rPosition, dataInterface->robotMovementInterface->robot-CurrentDirection);
			
		
			while (Forward.data.kind == HAZARD)					//�տ� �ִ� ��尡 Hazard�� �ƴҶ����� ȸ��.
			{
				GetNextMoveData();
				Forward = mapManager->GetForwardMapNode(dataInterface->robotMovementInterface->robot.robotPosition, dataInterface->robotMovementInterface->robot.CurrentDirection);
				AnalyzeHazardSensorData();
			}

			dataInterface->robotMovementInterface->robot.Move();//���� �κ� move
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
	dataInterface->UseSensor(HAZARD_SENSOR, result, mapManager->mapModel, dataInterface->robotMovementInterface->robot.rPosition, dataInterface->robotMovementInterface->robot.rDirection);
	mapManager->AddHazardPoint(*(int*)result);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface->UseColorSensor(result, mapManager->mapModel, dataInterface->robotMovementInterface->robot.rPosition, dataInterface->robotMovementInterface->robot.rDirection);
	mapManager->AddColorBlob(*(int*)result);
}