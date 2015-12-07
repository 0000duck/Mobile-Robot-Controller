/*
Map�� ���� �Է���
�켱�� 2���� ������ �Ѵٰ� �����Ѵ�.

*/
#pragma once
#include"Common.h"
class DataObject
{
public:
	int kind;
};

class MapNode
{
public :
	bool isDetected;
	bool isSensed;
	Position position;
	DataObject data;
protected:
	
};

class MapModel
{
private:
	
public:
	MapModel(int width, int height);
	MapNode** getMapNode();
	int getMapHeight();
	int getMapWidth();
	int getMapData(int y, int x);
	void setMapData(int y, int x, int kind);
private:
	int mapWidth, mapHeight;
	MapNode** Map;
};
