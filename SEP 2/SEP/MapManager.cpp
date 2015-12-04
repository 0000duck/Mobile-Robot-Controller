
#include"mapmanager.h"
void MapManager::CreateMapModel(int** mapdata)//�Է������ ���� ���� ������
{

	//�켱�� ���� public���� �ϰ� ���߿� private���� �ٲ� ��ȹ
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			mapModel->Map[i][j].isDetected = false;
			mapModel->Map[i][j].PosX = i;
			mapModel->Map[i][j].PosY = j;
			if(mapdata[i][j]==HAZARD)
				mapModel->Map[i][j].data.kind=HAZARD;
			else
				mapModel->Map[i][j].data.kind = INIT;
			//map�� �Ӽ��� hazard�� �ƴϸ� INIT���� ����.
		}
	}

	CalAble(startx, starty);
	SetDisable();
	//���� ��ġ���� Ž���� �� ���� ������ HAZARD��� ǥ��.

	mapModel->Map[starty][startx].isDetected = true;
	//������ġ = Ž������� �ٲ�
}



void MapManager::AddColorBlob(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	//�켱 ����κ��� �������� ������ �ξ���. �Ŀ� ��� �������� �����Ѵ�.
	int t = 8;//���߿� �ϰ����ְ� �ٲ� 
	if (pos & 0x1000)
	{
		mapModel->Map[robotPos.y - 1][robotPos.x].data.kind = COLORBLOB;
	}
	if (pos & 0x0100)
	{
		mapModel->Map[robotPos.y][robotPos.x - 1].data.kind = COLORBLOB;
	}
	if (pos & 0x0010)
	{
		mapModel->Map[robotPos.y + 1][robotPos.x].data.kind = COLORBLOB;
	}
	if (pos & 0x0001)
	{
		mapModel->Map[robotPos.y][robotPos.x + 1].data.kind = COLORBLOB;
	}
}

void MapManager::AddHazardPoint(int pos, Position robotPos)// 8,4,2,6�� ������ 1000,0100,0010,0001�� ��Ÿ����.
{
	
	if (pos & 0x1000)
	{
		mapModel->Map[robotPos.y - 1][robotPos.x].data.kind = HAZARD;
	}
	if (pos & 0x0100)
	{
		mapModel->Map[robotPos.y][robotPos.x - 1].data.kind = HAZARD;
	}
	if (pos & 0x0010)
	{
		mapModel->Map[robotPos.y + 1][robotPos.x].data.kind = HAZARD;
	}
	if (pos & 0x0001)
	{
		mapModel->Map[robotPos.y][robotPos.x + 1].data.kind = HAZARD;
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
		y++;
		break;
	case 6:
		x++;
		break;
	case 2:
		y--;
		break;
	case 4:
		x--;
		break;
	}
	return mapModel->Map[robotPos.y + y][robotPos.x + x];

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
void MapManager::CalAble(int x, int y)					//x, y���� �� �� �ִ� ���� NORMAL�� ����.
{
	int i=x, j=y;

	if(i==mapWidth-1);
	else if(mapModel->Map[j][i+1].data.kind==HAZARD);
	else if(mapModel->Map[j][i+1].data.kind!=NORMAL)
	{
		mapModel->Map[j][i+1].data.kind=NORMAL;
		CalAble(i+1, j);
	}
	if(i==0);
	else if(mapModel->Map[j][i-1].data.kind==HAZARD);
	else if(mapModel->Map[j][i-1].data.kind!=NORMAL)
	{
		mapModel->Map[j][i-1].data.kind=NORMAL;
		CalAble(i-1, j);
	}
	if(j==mapHeight-1);
	else if(mapModel->Map[j+1][i].data.kind==HAZARD);
	else if(mapModel->Map[j+1][i].data.kind!=NORMAL)
	{
		mapModel->Map[j+1][i].data.kind=NORMAL;
		CalAble(i, j+1);
	}
	if(j==0);
	else if(mapModel->Map[j-1][i].data.kind==HAZARD);
	else if(mapModel->Map[j-1][i].data.kind!=NORMAL)
	{
		mapModel->Map[j-1][i].data.kind=NORMAL;
		CalAble(i, j-1);
	}

}
void MapManager::SetDisable()					//CalAble()�Ŀ��� INIT���� �����ִ� �κ��� ���� ���ϴ°����� ����, HAZARD�� ǥ��.
{
	int i, j;

	for(j=0; j<mapHeight; j++)
	{
		for(i=0; i<mapWidth; i++)
		{
			if(mapModel->Map[j][i].data.kind==INIT)
				mapModel->Map[j][i].data.kind=HAZARD;
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