
#include"mapmanager.h"
void MapManager::CreateMapModel()//�Է������ ���� ���� ������
{
	MapNode** Map = mapModel->getMapNode();
	//�켱�� ���� public���� �ϰ� ���߿� private���� �ٲ� ��ȹ
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			Map[i][j].isDetected = false;
			Map[i][j].position.x = i;
			Map[i][j].position.y = j;
			Map[i][j].isSensed = false;
				Map[i][j].data.kind = INIT;
			//map�� �Ӽ��� hazard�� �ƴϸ� INIT���� ����.
		}
	}

	CalAble(startx, starty);
	SetDisable();
	//���� ��ġ���� Ž���� �� ���� ������ HAZARD��� ǥ��.

	Map[starty][startx].isDetected = true;
	//������ġ = Ž������� �ٲ�
}



void MapManager::AddColorBlob(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	MapNode** Map = mapModel->getMapNode();
	//�켱 ����κ��� �������� ������ �ξ���. �Ŀ� ��� �������� �����Ѵ�.
	int t = 8;//���߿� �ϰ����ְ� �ٲ� 
	if (pos & UP)
	{
		Map[robotPos.y - 1][robotPos.x].data.kind = COLORBLOB;
	}
	if (pos & LEFT)
	{
		Map[robotPos.y][robotPos.x - 1].data.kind = COLORBLOB;
	}
	if (pos & DOWN)
	{
		Map[robotPos.y + 1][robotPos.x].data.kind = COLORBLOB;
	}
	if (pos & RIGHT)
	{
		Map[robotPos.y][robotPos.x + 1].data.kind = COLORBLOB;
	}
}

void MapManager::AddHazardPoint(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	MapNode** Map = mapModel->getMapNode();
	if (pos & UP)
	{
		Map[robotPos.y - 1][robotPos.x].data.kind = HAZARD;
	}
	if (pos & LEFT)
	{
		Map[robotPos.y][robotPos.x - 1].data.kind = HAZARD;
	}
	if (pos & DOWN)
	{
		Map[robotPos.y + 1][robotPos.x].data.kind = HAZARD;
	}
	if (pos & RIGHT)
	{
		Map[robotPos.y][robotPos.x + 1].data.kind = HAZARD;
	}
}

void MapManager::addHazardPointByPoint(int y, int x)
{
	MapNode** Map = mapModel->getMapNode();
	Map[y][x].data.kind = HAZARD;
}

void MapManager::addColorBlobPointByPoint(int y, int x)
{
	MapNode** Map = mapModel->getMapNode();
	Map[y][x].data.kind = COLORBLOB;
}
MapNode MapManager::GetForwardMapNode(Position robotPos, int robotDirection)//hazard ����
{
	int x = 0, y = 0;
		/*sensor.SensorUse(HAZARD_SENSOR, result);
	AddHazardPoint(*(int*)result);
	*/
	switch (robotDirection)
	{
	case 8:
		y--;
		break;
	case 6:
		x++;
		break;
	case 2:
		y++;
		break;
	case 4:
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
	else if (Map[j][i + 1].data.kind == HAZARD);
	else if (Map[j][i + 1].data.kind == INIT)
	{
		Map[j][i + 1].data.kind = NORMAL;
		CalAble(i + 1, j);
	}
	if (i == 0);
	else if (Map[j][i - 1].data.kind == HAZARD);
	else if (Map[j][i - 1].data.kind == INIT)
	{
		Map[j][i - 1].data.kind = NORMAL;
		CalAble(i - 1, j);
	}
	if (j == mapHeight - 1);
	else if (Map[j + 1][i].data.kind == HAZARD);
	else if (Map[j + 1][i].data.kind == INIT)
	{
		Map[j + 1][i].data.kind = NORMAL;
		CalAble(i, j + 1);
	}
	if (j == 0);
	else if (Map[j - 1][i].data.kind == HAZARD);
	else if (Map[j - 1][i].data.kind == INIT)
	{
		Map[j - 1][i].data.kind = NORMAL;
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
			if (Map[j][i].data.kind == INIT)
				Map[j][i].data.kind = HAZARD;
		}
	}
}
void MapManager::SearchDis(int type)
{
	int i, j;
	MapNode** Map = mapModel->getMapNode();

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{

			if (Map[i][j].data.kind == HAZARD);
			else if (Map[i][j].data.kind == COLORBLOB);
			else if (Map[i][j].data.kind == EXPLROATIONPOINT);
			else if ((type == 1) && (Map[i][j].data.kind == DIS));
			else
				Map[i][j].data.kind = INIT;
			//map�� �Ӽ��� hazard�� �ƴϸ� INIT���� ����.
		}
	}

	CalAble(startx, starty);
	SetDisable();

}