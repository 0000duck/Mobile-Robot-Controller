
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
			Map[i][j].position.x= i;
			Map[i][j].position.y = j;
			if(mapdata[i][j]==HAZARD)
				Map[i][j].data.kind=HAZARD;
			else
				Map[i][j].data.kind = INIT;
			//map의 속성이 hazard가 아니면 INIT으로 설정.
		}
	}

	CalAble(startx, starty);
	SetDisable();
	//현재 위치에서 탐사할 수 없는 영역을 HAZARD라고 표시.

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
void MapManager::CalAble(int x, int y)					//x, y에서 갈 수 있는 곳을 NORMAL로 셋팅.
{
	int i=x, j=y;
	MapNode** Map = mapModel->getMapNode();

	if(i==mapWidth-1);
	else if(Map[j][i+1].data.kind==HAZARD);
	else if(Map[j][i+1].data.kind!=NORMAL)
	{
		Map[j][i+1].data.kind=NORMAL;
		CalAble(i+1, j);
	}
	if(i==0);
	else if(Map[j][i-1].data.kind==HAZARD);
	else if(Map[j][i-1].data.kind!=NORMAL)
	{
		Map[j][i-1].data.kind=NORMAL;
		CalAble(i-1, j);
	}
	if(j==mapHeight-1);
	else if(Map[j+1][i].data.kind==HAZARD);
	else if(Map[j+1][i].data.kind!=NORMAL)
	{
		Map[j+1][i].data.kind=NORMAL;
		CalAble(i, j+1);
	}
	if(j==0);
	else if(Map[j-1][i].data.kind==HAZARD);
	else if(Map[j-1][i].data.kind!=NORMAL)
	{
		Map[j-1][i].data.kind=NORMAL;
		CalAble(i, j-1);
	}

}
void MapManager::SetDisable()					//CalAble()후에도 INIT으로 남아있는 부분은 가지 못하는곳으로 간주, HAZARD로 표시.
{
	int i, j;
	MapNode** Map = mapModel->getMapNode();

	for(j=0; j<mapHeight; j++)
	{
		for(i=0; i<mapWidth; i++)
		{
			if(Map[j][i].data.kind==INIT)
				Map[j][i].data.kind=HAZARD;
		}
	}
}
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
