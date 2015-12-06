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
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	int i;

	dis = (int**)malloc((sizeof(int)*mapWidth*mapHeight));
	for (i = 0; i < mapHeight; i++)
	{
		dis[i] = (int*)malloc((sizeof(int)*mapWidth));
	}
	InitDis();
	dis[CurrentTarget.position.y][CurrentTarget.position.x] = 0;
	while (DisEnd())
		CalPath(CurrentTarget.position.x, CurrentTarget.position.y);
}
void MoveManager::InitDis()                              //dis �ʱ�ȭ
{
	int i, j;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();

	for (j = 0; j < mapHeight; j++)
	{
		for (i = 0; i<mapWidth; i++)
			dis[j][i] = UNKNOWN;
	}

}
void MoveManager::CalPath(int x, int y)							//��忡�� ��ǥ���������� �Ÿ��� ����ϴ� �κ�. ������ ��� �뵵�θ� ���� ��.
{
	int i = x, j = y;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	if (Map[y][x].data.kind == HAZARD);						//hazard�� ������� ����.
	else
	{
		if ((i != mapWidth - 1) && (dis[j][i + 1]>dis[j][i] + 1))			//������ �˻�
		{
			if (Map[j][i + 1].data.kind == HAZARD);
			else
			{
				dis[j][i + 1] = dis[j][i] + 1;
				CalPath(i + 1, j);
			}
		}
		if ((i != 0) && (dis[j][i - 1]>dis[j][i] + 1))			//���� �˻�
		{
			if (Map[j][i - 1].data.kind == HAZARD);
			else
			{
				dis[j][i - 1] = dis[j][i] + 1;
				CalPath(i - 1, j);
			}
		}
		if ((j != mapHeight - 1) && (dis[j + 1][i]>dis[j][i] + 1))			//���� �˻�
		{
			if (Map[j + 1][i].data.kind == HAZARD);
			else
			{
				dis[j + 1][i] = dis[j][i] + 1;
				CalPath(i, j + 1);
			}
		}
		if ((j != 0) && (dis[j - 1][i]>dis[j][i] + 1))			//�Ʒ��� �˻�
		{
			if (Map[j - 1][i].data.kind == HAZARD);
			else					{
				dis[j - 1][i] = dis[j][i] + 1;
				CalPath(i, j - 1);
			}
		}
	}
}
int MoveManager::DisEnd()					//dis�� ��� ���ƴ��� Ȯ��
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
		return 0;//��������
	else
	{
		return POSITIONING_ERROR;
	}
	delete result;
}int MoveManager::MakeNextMoveData(int prev)					//�� �״�� ���� ������ �����ϴ� ��
{
	int val, tmp = 0;
	int robotx = dataInterface->getRobotPosition().x;
	int	roboty = dataInterface->getRobotPosition().y;
	int mapWidth = mapModel->getMapWidth();
	int mapHeight = mapModel->getMapHeight();

	val = dis[roboty][robotx];

	while (/*(val - dis[roboty][robotx])<2*/1)
	{
		if ((roboty<mapHeight - 1) && (val == dis[roboty + 1][robotx] + 1) && (Map[roboty + 1][robotx].data.kind != HAZARD) && (Map[roboty + 1][robotx].data.kind != DIS) && (prev != 8))
			tmp = 2;
		if (tmp == 0&&(robotx<mapWidth - 1) && (val == dis[roboty][robotx + 1] + 1) && (Map[roboty][robotx + 1].data.kind != HAZARD) && (Map[roboty][robotx + 1].data.kind != DIS) && (prev != 4))
			tmp = 6;
		if (tmp == 0 && (roboty>0) && (val == dis[roboty - 1][robotx] + 1) && (Map[roboty - 1][robotx].data.kind != HAZARD) && (Map[roboty - 1][robotx].data.kind != DIS) && (prev != 2))
			tmp = 8;
		if (tmp == 0 && (robotx>0) && (val == dis[roboty][robotx - 1] + 1) && (Map[roboty][robotx - 1].data.kind != HAZARD) && (Map[roboty][robotx - 1].data.kind != DIS) && (prev != 6))
			tmp = 4;
		
		if (tmp != 0)
			break;
		else
			val++;
	}
	if (tmp == 0)
	{
		int a=4;
	/*
		Map[roboty][robotx].data.kind = DIS;

		if (prev == 8)
			return 2;
		if (prev == 4)
			return 6;
		if (prev == 6)
			return 4;
		if (prev == 2)
			return 8;
			*/
	}

	return tmp;

}
void MoveManager::GetNextMoveData(int prev)					//������ �������� �κ��� ������ ��
{
	int MData;

	MData = MakeNextMoveData(prev);


	virtualRobot->virtualRotate(MData);

	dataInterface->requestRobotRotate(MData);

}

//�̰Ÿ� ���� �־ Analyze�Լ��鿡�� ��� ������� �𸣰����� �ϴ� �ϰ��� �ְ� ����.
void MoveManager::GetPositioningSensorData(void *result)//�켱 ������ �ִ´�.
{
	dataInterface->UseSensor(POSITIONING_SENSOR, result, mapModel, dataInterface->getRobotPosition(), dataInterface->getRobotDirection());

	//AnalyzePositioningSensorData(*(Position *)result);//���⼭ Analyze���� ���� ������ �𸣰ڴ�
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

	dataInterface = new DataInterface(start, 2);
	virtualRobot = new VirtualRobot(start, 2);;// 2�� ó�� �ٶ󺸴� ������ 2�� �����̶�� ��
	SetMapModel(mapWidth, mapHeight, start);

	mapModel = mapManager->getMapModel();
	Map = mapModel->getMapNode();
}

int MoveManager::generator(){
	return ran.get();
}

void MoveManager::addExplorationPoint(int y, int x)
{
	MapNode m;
	m.position.y = y;
	m.position.x = x;
	Map[y][x].data.kind = EXPLROATIONPOINT;
	RemainSearchSpotList.push_front(m);
}

void MoveManager::Explore()
{
	MapNode Forward;
	int mapWidth = mapManager->getMapWidth();
	int mapHeight = mapManager->getMapHeight();
	int i;
	int prev = 0;

	while (RemainSearchSpotList.size() > 0)					//��� ��ǥ������ Ž���ϴ� ����
	{
		CurrentTarget = RemainSearchSpotList.front();
		Map[CurrentTarget.position.y][CurrentTarget.position.x].data.kind = EXPLROATIONPOINT;
		mapManager->SearchDis(0);
		if (Map[CurrentTarget.position.y][CurrentTarget.position.x].data.kind == HAZARD)
		{
			
			printf("can't explore\n");
			RemainSearchSpotList.pop_front();
			continue;
		}

		InitializeMoveData();

		while ((dataInterface->getRobotPosition().x != CurrentTarget.position.x) || (dataInterface->getRobotPosition().y != CurrentTarget.position.y))				//�� ��ǥ������ Ž���ϴ� ����
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
					else if (Map[j][k].data.kind == COLORBLOB)
						printf("C ");
					else if (Map[j][k].data.kind ==DIS )
						printf("D ");
					else printf("  ");
				}
				printf("\n");
			}

			if (Map[CurrentTarget.position.y][CurrentTarget.position.x].data.kind == HAZARD)
			{
				printf("can't explore\n");
				RemainSearchSpotList.pop_front();
				continue;
			}
			mapManager->SearchDis(1);

			AnalyzePositioningSensorData();

			GetNextMoveData(prev);
			AnalyzeHazardSensorData();
			AnalyzeColorSensorData();
			Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());


			while (Forward.data.kind == HAZARD)					//�տ� �ִ� ��尡 Hazard�� �ƴҶ����� ȸ��.
			{
				InitDis();
				dis[CurrentTarget.position.y][CurrentTarget.position.x] = 0;
				while (DisEnd())
				{
					CalPath(CurrentTarget.position.x, CurrentTarget.position.y);
				}
				mapManager->SearchDis(1);
				GetNextMoveData(prev);
				Forward = mapManager->GetForwardMapNode(dataInterface->getRobotPosition(), dataInterface->getRobotDirection());
				AnalyzeHazardSensorData();
			}
			//���� �ִ����� ǥ����

			prev = dataInterface->getRobotDirection();

			RobotMoveRequest();
			possibleError();// ��������� �ѹ� ������(�����ϴ� �ſ��� �Ȱ�)
			printf(" (%d,%d) \n", dataInterface->getRobotPosition().y, dataInterface->getRobotPosition().x);


		}
		printf(" Ž�� �Ϸ� ����ġ : (%d,%d) \n", dataInterface->getRobotPosition().y, dataInterface->getRobotPosition().x);

		RemainSearchSpotList.pop_front();					//Ž�簡 �Ϸ�Ǿ����� ����Ʈ���� ����

		for (i = 0; i < mapHeight; i++)			//�Ҵ���� �޸� �ݳ�
			free(dis[i]);
		free(dis);

	}

}

void MoveManager::RobotMoveRequest()
{
	//���� ��ġ�� ����
	mapManager->setPreviousNode(dataInterface->getRobotPosition());
	//���� ������ �߰�(PositioningSensor*)
	//���� �κ� ��ġ ����
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
			//���� ���������� ��
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
void MoveManager::AnalyzeHazardSensorData()//ó��������
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
			printf("error �߻� 2ĭ �̵�\n");
			dataInterface->requestRobotMove();
			setPositioningSensor();
			}
	}
	
}