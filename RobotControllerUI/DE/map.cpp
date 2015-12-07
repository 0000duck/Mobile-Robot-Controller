#include"map.h"





//실제 맵이 아닌 입력받은 가상 맵
MapModel::MapModel(int width, int height)//Map을 입력받고 초기화
{
	Map = new MapNode*[height];
	for (int i = 0; i < height; i++)
	{
		Map[i] = new MapNode[width];
	}
	mapHeight = height;
	mapWidth = width;
}
MapNode** MapModel::getMapNode()
{
	return Map;
}

int MapModel::getMapHeight()
{
	return mapHeight;
}
int MapModel::getMapWidth()
{
	return mapWidth;
}

// 여기 수정함
// y 좌표
int MapModel::getMapData(int y, int x)
{
	return Map[y][x].data.kind;
}
void MapModel::setMapData(int y, int x, int kind)
{
	Map[y][x].data.kind = kind;
}