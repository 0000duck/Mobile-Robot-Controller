#include"map.h"





//���� ���� �ƴ� �Է¹��� ���� ��
MapModel::MapModel(int width, int height)//Map�� �Է¹ް� �ʱ�ȭ
{
	Map = new MapNode*[height];
	for (int i = 0; i < width; i++)
	{
		Map[i] = new MapNode();
	}
}

