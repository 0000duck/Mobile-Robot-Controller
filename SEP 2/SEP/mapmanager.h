#pragma once
#include"global.h"
#include"Common.h"
#include"map.h"

class MapManager
{
public:
	void CreateMapModel(int** mapdata);
	int GetNearMapNodeData();
	void AddColorBlob(int colorblobInfo, Position pos);
	void AddHazardPoint(int hazardInfo, Position pos);
	MapNode GetForwardMapNode(Position robotPos, int robotDirection);
	MapNode PreviousNode;

	int mapWidth, mapHeight;
	MapModel *mapModel;
	MapManager(int** mapInput, int mapX, int mapY, Position Start);
private:
	void AnalyzeMapData();
	int startx, starty;

};