#include"mapmanager.h"
#include"map.h"
#include"global.h"
int MapManager::CreateMapModel(int** mapdata)//�Է������ ���� ���� ������
{

	//�켱�� ���� public���� �ϰ� ���߿� private���� �ٲ� ��ȹ
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			mapModel.Map[i][j].isDetected = false;
			mapModel.Map[i][j].PosX = i;
			mapModel.Map[i][j].PosY = j;
			mapModel.Map[i][j].data.kind = mapdata[i][j];//map�� �Ӽ��� hazard���� exploration points ���� ��� ����
		}
	}
	mapModel.Map[startx][starty].isDetected = true;
	//������ġ = Ž������� �ٲ�
}



void MapManager::AddColorBlob(int pos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	//�켱 ����κ��� �������� ������ �ξ���. �Ŀ� ��� �������� �����Ѵ�.
	int t = 8;//���߿� �ϰ����ְ� �ٲ� 
	if (pos & 0x1000)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x][virtualRobot.CurrentPosition.y - 1].data.kind = COLORBLOB;
	}
	if (pos & 0x0100)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x - 1][virtualRobot.CurrentPosition.y].data.kind = COLORBLOB;
	}
	if (pos & 0x0010)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x][virtualRobot.CurrentPosition.y + 1].data.kind = COLORBLOB;
	}
	if (pos & 0x0001)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x + 1][virtualRobot.CurrentPosition.y].data.kind = COLORBLOB;
	}
}

void MapManager::AddHazardPoint(int pos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	
	if (pos & 0x1000)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x][virtualRobot.CurrentPosition.y - 1].data.kind = HAZARD;
	}
	if (pos & 0x0100)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x - 1][virtualRobot.CurrentPosition.y].data.kind = HAZARD;
	}
	if (pos & 0x0010)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x][virtualRobot.CurrentPosition.y + 1].data.kind = HAZARD;
	}
	if (pos & 0x0001)
	{
		mapModel.Map[virtualRobot.CurrentPosition.x + 1][virtualRobot.CurrentPosition.y].data.kind = HAZARD;
	}
}

MapNode MapManager::GetForwardMapNode(Position robotPos, int robotDirection)//hazard ����
{
	void* result;
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
	return mapModel.Map[robotPos.x+x][robotPos.y+y];

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
	CreateMapModel(mapInput);
}