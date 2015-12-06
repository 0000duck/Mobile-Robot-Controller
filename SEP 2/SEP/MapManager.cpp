
#include"mapmanager.h"
void MapManager::CreateMapModel()//�Է������ ���� ���� ������
{
	//�켱�� ���� public���� �ϰ� ���߿� private���� �ٲ� ��ȹ
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			setMapInfo(false, i, j, false, INIT);
			//map�� �Ӽ��� hazard�� �ƴϸ� INIT���� ����.
		}
	}

	CalAble(startx, starty);
	SetDisable();
	//���� ��ġ���� Ž���� �� ���� ������ HAZARD��� ǥ��.

	setMapInfo(true, starty, startx, false, INIT);
	//������ġ = Ž������� �ٲ�
}


//			�ٲ��ٲ��� �Ͷ� y�夡y��
//
//
//
//

void MapManager::AddColorBlob(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	MapNode** Map = mapModel->getMapNode();
	//�켱 ����κ��� �������� ������ �ξ���. �Ŀ� ��� �������� �����Ѵ�.
	if (pos & UP)
	{
		setMapData(robotPos.y, robotPos.x, COLORBLOB);
	}
	if (pos & LEFT)
	{
		setMapData(robotPos.y, robotPos.x - 1, COLORBLOB);
	}
	if (pos & DOWN)
	{
		setMapData(robotPos.y, robotPos.x, COLORBLOB);
	}
	if (pos & RIGHT)
	{
		setMapData(robotPos.y, robotPos.x + 1, COLORBLOB);
	}
}

void MapManager::AddHazardPoint(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	MapNode** Map = mapModel->getMapNode();
	if (pos & UP)
	{
		setMapData(robotPos.y + 1 , robotPos.x, HAZARD);
	}
	if (pos & LEFT)
	{
		setMapData(robotPos.y, robotPos.x-1, HAZARD);
	}
	if (pos & DOWN)
	{
		setMapData(robotPos.y - 1 , robotPos.x, HAZARD);
	}
	if (pos & RIGHT)
	{
		setMapData(robotPos.y, robotPos.x+1, HAZARD);
	}
}

void MapManager::addHazardPointByPoint(int y, int x)
{
	setMapData(y, x, HAZARD);
}

void MapManager::addColorBlobPointByPoint(int y, int x)
{
	setMapData(y, x, HAZARD);
}
MapNode MapManager::GetForwardMapNode(Position robotPos, int robotDirection)//hazard ����
{
	int x = 0, y = 0;
		/*sensor.SensorUse(HAZARD_SENSOR, result);
	AddHazardPoint(*(int*)result);
	*/
	switch (robotDirection)
	{
	case UP:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y--;
		break;
	case LEFT:
		x--;
		break;
	}
	return mapModel->getMapNode()[robotPos.y + y][robotPos.x + x];

}
/*Ž�� ����� �ٲ�� �����ʰԵ�
int MapManager::GetNearMapNodeData()// colorblob ����
{
	void* result;
	sensor.SensorUse(COLORBLOB_SENSOR, result);
	AddHazardPoint(*(int*)result);
}
*/
/*
void MapManager::AnalyzeMapData()
{
	//���ϴ��� �� �𸣰ڴ�
}
*/
MapManager::MapManager( int mapX, int mapY,Position start)
{
	mapWidth = mapX;
	mapHeight = mapY;
	startx = start.x;
	starty = start.y;

	mapModel = new MapModel(mapX, mapY);

	CreateMapModel();

}

MapModel* MapManager::getMapModel()
{
	return mapModel;
}
int MapManager::getMapWidth()
{
	return mapWidth;
}

int MapManager::getMapHeight()
{
	return mapHeight;
}

MapNode MapManager::getPreviousNode()
{
	return PreviousNode;
}
void MapManager::setPreviousNode(Position pos)
{
	PreviousNode.position = pos;
}



void MapManager::CalAble(int x, int y)					//x, y���� �� �� �ִ� ���� NORMAL�� ����.
{
	int i = x, j = y;
	MapNode** Map = mapModel->getMapNode();

	if (i == mapWidth - 1);
	else if (getMapData(j, i+1) == HAZARD);
	else if (getMapData(j, i+1) == INIT)
	{
		setMapData(j,i+1,NORMAL);
		CalAble(i + 1, j);
	}
	if (i == 0);
	else if (getMapData(j, i - 1) == HAZARD);
	else if (getMapData(j, i - 1) == INIT)
	{
		setMapData(j, i - 1,NORMAL);
		CalAble(i - 1, j);
	}
	if (j == mapHeight - 1);
	else if (getMapData(j+1, i ) == HAZARD);
	else if (getMapData(j + 1, i) == INIT)
	{
		setMapData(j + 1, i,NORMAL);
		CalAble(i, j + 1);
	}
	if (j == 0);
	else if (getMapData(j -1, i) == HAZARD);
	else if (getMapData(j - 1, i) == INIT)
	{
		setMapData(j - 1, i,NORMAL);
		CalAble(i, j - 1);
	}

}
void MapManager::SetDisable()					//CalAble()�Ŀ��� INIT���� �����ִ� �κ��� ���� ���ϴ°����� ����, HAZARD�� ǥ��.
{
	int i, j;
	MapNode** Map = mapModel->getMapNode();

	for (j = 0; j<mapHeight; j++)
	{
		for (i = 0; i<mapWidth; i++)
		{
			if (getMapData(j,i)== INIT)
				setMapData(j,i, HAZARD);
		}
	}
}
void MapManager::SearchDis(int type)
{
	int i, j;


	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{

			if (getMapData(i,j)== HAZARD);
			else if (getMapData(i, j) == COLORBLOB);
			else if (getMapData(i, j) == EXPLROATIONPOINT);
			else if ((type == 1) && (getMapData(i, j) == DIS));
			else
				setMapData(i,j,INIT);
			//map�� �Ӽ��� hazard�� �ƴϸ� INIT���� ����.
		}
	}

	CalAble(startx, starty);
	SetDisable();

}

int MapManager::getMapData(int y, int x)
{
	return mapModel->getMapData(y, x);
}
void MapManager::setMapData(int y, int x, int kind)
{
	mapModel->setMapData(y, x, kind);
}


void MapManager::setMapInfo(bool isDetected, int y, int x, bool isSensed, int kind)
{
	MapNode** Map = mapModel->getMapNode();
	Map[y][x].isDetected = isDetected;
	Map[y][x].position.y = y;
	Map[y][x].position.x = x;
	Map[y][x].isSensed = isSensed;
	Map[y][x].data.kind = kind;
}