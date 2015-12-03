#include"moveManager.h"
#include"global.h"

#define UNKNOWN 1000

void MoveManager::InitializeMoveData()
{
	InitDis();
	CalPath(CurrentPosition.x, CurrentPosition.y);
	
}
void InitDis()										//dis �ʱ�ȭ
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

void CalPath(int x, int y)							//��忡�� ��ǥ���������� �Ÿ��� ����ϴ� �κ�. ������ ��� �뵵�θ� ���� ��.
{
	int i, j;

	if(mapManager.mapModel.Map[x][y].kind==HAZARD);						//hazard�� ������� ����.
	else if((Current.PosX>x)&&(Current.PosY>y))						//Current�� �������� x, y�� 3��и鿡 ���� ��
		CalThird(x, y);
	else if ((Current.PosX>x) && (Current.PosY<y))					//Current�� �������� x, y�� 2��и鿡 ���� ��
		CalSecond(x, y);
	else if ((Current.PosX<x) && (Current.PosY>y))					//Current�� �������� x, y�� 4��и鿡 ���� ��
		CalFourth(x, y);
	else if ((Current.PosX<x) && (Current.PosY < y))				//Current�� �������� x, y�� 1��и鿡 ���� ��
		CalFirst(x, y);
	else if(x==Current.PosX)								//Current�� x, y�� x������ �������� �������� ��
	{
		if(y<Current.PosY)					//Current�� �������� x, y�� ���ʿ� ���� ��
		{
			for(j=y; j<Current.PosY; j++)
			{
				if(Map[x][j+1].kind==HAZARD);
				else if(dis[x][j+1]>dis[x][j]+1)
					dis[x][j+1]=dis[x][j]+1;
			}
		}
		else										//Current�� �������� x, y�� �����ʿ� ���� ��
		{
			for(j=y; j>Current.PosY; j--)
			{
				if(Map[x][j-1].kind==HAZARD);
				else if(dis[x][j-1]>dis[x][j]+1)
					dis[x][j-1]=dis[x][j]+1;
			}
		}
	}
	else if(y==Current.PosY)								//Current�� x, y�� y������ �������� �������� ��
	{
		if(x<Current.PosX)					//Current�� �������� x, y�� ���ʿ� ���� ��
		{
			for(i=x; i<Current.PosX; i++)
			{
				if(Map[i+1][y].kind==HAZARD);
				else if(dis[i+1][y]>dis[i][y]+1)
					dis[i+1][y]=dis[i][y]+1;
			}
		}
		else										//Current�� �������� x, y�� �Ʒ��ʿ� ���� ��
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
void CalFirst(int x, int y)				//Current�� �������� ��ǥ������ 1��и鿡 ���� ��
{
	int i, j;

	for (i = x; i>Current.PosX; i--)
	{
		for (j = y; j>Current.PosY; j--)
		{
			if ((i != x)&&(dis[i + 1][j]>dis[i][j] + 1))			//�Ʒ��� �˻�
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i != Current.PosX)&&(dis[i - 1][j]>dis[i][j] + 1))			//���� �˻�
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j != y)&(dis[i][j + 1]>dis[i][j] + 1))			//������ �˻�
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j != Current.PosY)&&(dis[i][j - 1]>dis[i][j] + 1))			//���� �˻�
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
void CalSecond(int x, int y)				//Current�� �������� ��ǥ������ 2��и鿡 ���� ��
{
	int i, j;

	for (i = x; i<Current.PosX; i++)
	{
		for (j = y; j>Current.PosY; j--)
		{
			if ((i != Current.PosX)&&(dis[i + 1][j]>dis[i][j] + 1))			//�Ʒ��� �˻�
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i != x)&&(dis[i - 1][j]>dis[i][j] + 1))			//���� �˻�
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j != y)&&(dis[i][j + 1]>dis[i][j] + 1))			//������ �˻�
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j != Current.PosY)&&(dis[i][j - 1]>dis[i][j] + 1))			//���� �˻�
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
void CalThird(int x, int y)				//Current�� �������� ��ǥ������ 3��и鿡 ���� �� 
{
	int i, j;

	for (i = x; i<Current.PosX; i++)
	{
		for (j = y; j<Current.PosY; j++)
		{
			if ((i!=Current.PosX)&&(dis[i + 1][j]>dis[i][j] + 1))			//�Ʒ��� �˻�
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i!=x)&&(dis[i - 1][j]>dis[i][j] + 1))			//���� �˻�
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j!=Current.PosY)&&(dis[i][j + 1]>dis[i][j] + 1))			//������ �˻�
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j!=y)&&(dis[i][j - 1]>dis[i][j] + 1))			//���� �˻�
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
void CalFourth(int x, int y)				//Current�� �������� ��ǥ������ 4��и鿡 ���� ��
{
	int i, j;

	for (i = x; i>Current.PosX; i--)
	{
		for (j = y; j<Current.PosY; j++)
		{
			if ((i != x)&&(dis[i + 1][j]>dis[i][j] + 1))			//�Ʒ��� �˻�
			{
				if(Map[i+1][j].kind==HAZARD);
				else
				{
					dis[i + 1][j] = dis[i][j] + 1;
					CalPath(i + 1, j);
				}
			}
			if ((i != Current.PosX)&&(dis[i - 1][j]>dis[i][j] + 1))			//���� �˻�
			{
				if(Map[i-1][j].kind==HAZARD);
				else
				{
					dis[i - 1][j] = dis[i][j] + 1;
					CalPath(i - 1, j);
				}
			}
			if ((j != Current.PosY)&&(dis[i][j + 1]>dis[i][j] + 1))			//������ �˻�
			{
				if(Map[i][j+1].kind==HAZARD);
				else
				{
					dis[i][j + 1] = dis[i][j] + 1;
					CalPath(i, j + 1);
				}
			}
			if ((j != y)&&(dis[i][j - 1]>dis[i][j] + 1))			//���� �˻�
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
	virtualRobot.CurrentDirection = MData;
	dataInterface.robotMovementInterface.robot.Rotate(MData);
	


}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface.UseSensor(POSITIONING_SENSOR, result);

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
}

MoveManager::MoveManager(int** mapInput, Position start)
{
	SetMapModel(mapInput);
	dataInterface.robotMovementInterface.robot.robotPosition.x = start.x;//���߿� �Լ��� �ٲ�
	dataInterface.robotMovementInterface.robot.robotPosition.y = start.y;
	virtualRobot(start);	//������ȣ��
}

void MoveManager::Explore()
{
	MapNode Forward;
	int i;

	while(RemainSearchSpotList.size() > 0)					//��� ��ǥ������ Ž���ϴ� ����
	{
		InitializeMoveData();

		while ((CurrentPosition.x!=CurrentTarget.PosX)||(CurrentPosition.y!=CurrentTarget.PosY))				//�� ��ǥ������ Ž���ϴ� ����
		{
			AnalyzePositioningSensorData();
			
			GetNextMoveData();
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager.GetForwardMapNode(dataInterface.robotMovementInterface.robot.robotPosition, dataInterface.robotMovementInterface.robot.CurrentDirection);
			
			while (Forward.data.kind == HAZARD)					//�տ� �ִ� ��尡 Hazard�� �ƴҶ����� ȸ��.
			{
				GetNextMoveData();
				Forward = mapManager.GetForwardMapNode(dataInterface.robotMovementInterface.robot.robotPosition, dataInterface.robotMovementInterface.robot.CurrentDirection);
				AnalyzeHazardSensorData();
			}

			dataInterface.robotMovementInterface.robot.Move();//���� �κ� move
			virtualRobot.VirtualMove();

		}

		RemainSearchSpotList.pop_front();					//Ž�簡 �Ϸ�Ǿ����� ����Ʈ���� ����
		
		for (i = 0; i < mapManager.mapHeight; i++)			//�Ҵ���� �޸� �ݳ�
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
		//���� ���������� ��
	}
}
void MoveManager::AnalyzeHazardSensorData()//ó��������
{
	void *result;
	dataInterface.UseSensor(HAZARD_SENSOR, result);//����� 4���� �� �޾ƿ��Ƿ� �׿� �°� �Լ��� «
	mapManager.AddHazardPoint(*(int*)result);
}

void MoveManager::AnalyzeColorSensorData()
{
	void *result;
	dataInterface.UseColorSensor(result);
	mapManager.AddColorBlob(*(int*)result);
}