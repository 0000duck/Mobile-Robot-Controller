#include"map.h"





//실제 맵이 아닌 입력받은 가상 맵
MapModel::MapModel(int width, int height)//Map을 입력받고 초기화
{
	Map = new MapNode*[height];
	for (int i = 0; i < height; i++)
	{
		Map[i] = new MapNode[width];
	}
}
MapNode** MapModel::getMapNode()
{
	return Map;
}

