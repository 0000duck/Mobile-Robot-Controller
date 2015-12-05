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
	MapNode GetForwardMapNode(Position position, int robotDirection);
	MapManager(int** mapInput, int mapX, int mapY, Position Start);
	MapModel * getMapModel();
	int getMapWidth();
	int getMapHeight();
	MapNode getPreviousNode();
	void setPreviousNode(Position pos);
	void SearchDis();
private:
	MapNode PreviousNode;
	int mapWidth, mapHeight;
	MapModel *mapModel;
	void AnalyzeMapData();
	int startx, starty;
	void CalAble(int x, int y);
	void SetDisable();
};