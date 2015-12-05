/*
Map에 대한 입력은
우선은 2차원 수열로 한다고 가정한다.

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
private:
	int mapWidth, mapHeight;
	MapNode** Map;
};
