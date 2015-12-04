
#include"mapmanager.h"
void MapManager::CreateMapModel(int** mapdata)//입력을어떻게 할지 아직 못정함
{
	MapNode** Map = mapModel->getMapNode();
	//우선은 전부 public으로 하고 나중에 private으로 바꿀 계획
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			Map[i][j].isDetected = false;
			Map[i][j].position.x = j;
			Map[i][j].position.y = i;
			Map[i][j].data.kind = mapdata[i][j];//map의 속성이 hazard인지 exploration points 인지 등등 설정
		}
	}
	Map[starty][startx].isDetected = true;
	//현재위치 = 탐험됨으로 바꿈
}



void MapManager::AddColorBlob(int pos, Position robotPos)// 8,4,2,6의 방향을 1000,0100,0010,0001로 나타낸다.
{
	MapNode** Map = mapModel->getMapNode();
	//우선 가상로봇을 전역으로 선언해 두었다. 후에 어디서 선언할지 결정한다.
	int t = 8;//나중에 일관성있게 바꿈 
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

void MapManager::AddHazardPoint(int pos, Position robotPos)// 8,4,2,6의 방향을 1000,0100,0010,0001로 나타낸다.
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

MapNode MapManager::GetForwardMapNode(Position robotPos, int robotDirection)//hazard 감지
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
/*탐사 방식이 바뀌어 쓰지않게됨
int MapManager::GetNearMapNodeData()// colorblob 감지
{
	void* result;
	sensor.SensorUse(COLORBLOB_SENSOR, result);
	AddHazardPoint(*(int*)result);
}
*/
/*
void MapManager::AnalyzeMapData()
{
	//뭘하는지 잘 모르겠다
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
