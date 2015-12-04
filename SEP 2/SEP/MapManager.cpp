
#include"mapmanager.h"
void MapManager::CreateMapModel(int** mapdata)//�Է������ ���� ���� ������
{
	MapNode** Map = mapModel->getMapNode();
	//�켱�� ���� public���� �ϰ� ���߿� private���� �ٲ� ��ȹ
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			Map[i][j].isDetected = false;
			Map[i][j].position.x = j;
			Map[i][j].position.y = i;
			Map[i][j].data.kind = mapdata[i][j];//map�� �Ӽ��� hazard���� exploration points ���� ��� ����
		}
	}
	Map[starty][startx].isDetected = true;
	//������ġ = Ž������� �ٲ�
}



void MapManager::AddColorBlob(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	MapNode** Map = mapModel->getMapNode();
	//�켱 ����κ��� �������� ������ �ξ���. �Ŀ� ��� �������� �����Ѵ�.
	int t = 8;//���߿� �ϰ����ְ� �ٲ� 
	if (pos & 0x1000)
	{
		Map[robotPos.y - 1][robotPos.x].data.kind = COLORBLOB;
	}
	if (pos & 0x0100)
	{
		Map[robotPos.y][robotPos.x - 1].data.kind = COLORBLOB;
	}
	if (pos & 0x0010)
	{
		Map[robotPos.y + 1][robotPos.x].data.kind = COLORBLOB;
	}
	if (pos & 0x0001)
	{
		Map[robotPos.y][robotPos.x + 1].data.kind = COLORBLOB;
	}
}

void MapManager::AddHazardPoint(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	MapNode** Map = mapModel->getMapNode();
	if (pos & 0x1000)
	{
		Map[robotPos.y - 1][robotPos.x].data.kind = HAZARD;
	}
	if (pos & 0x0100)
	{
		Map[robotPos.y][robotPos.x - 1].data.kind = HAZARD;
	}
	if (pos & 0x0010)
	{
		Map[robotPos.y + 1][robotPos.x].data.kind = HAZARD;
	}
	if (pos & 0x0001)
	{
		Map[robotPos.y][robotPos.x + 1].data.kind = HAZARD;
	}
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
MapManager::MapManager(int** mapInput, int mapX, int mapY,Position start)
{
	mapWidth = mapX;
	mapHeight = mapY;
	startx = start.x;
	starty = start.y;

	mapModel = new MapModel(mapX, mapY);

	CreateMapModel(mapInput);

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
