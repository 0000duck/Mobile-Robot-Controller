#include"map.h"





//���� ���� �ƴ� �Է¹��� ���� ��
MapModel::MapModel(int width, int height)//Map�� �Է¹ް� �ʱ�ȭ
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