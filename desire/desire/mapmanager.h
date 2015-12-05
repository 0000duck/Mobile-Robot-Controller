#pragma once
#include"global.h"
#include"Common.h"
#include"map.h"

class MapManager
{
public:
	void CreateMapModel();
	int GetNearMapNodeData();
	void AddColorBlob(int colorblobInfo, Position pos);
	void AddHazardPoint(int hazardInfo, Position pos);
	MapNode GetForwardMapNode(Position position, int robotDirection);
	MapManager( int mapX, int mapY, Position Start);
	MapModel * getMapModel();
	int getMapWidth();
	int getMapHeight();
	MapNode getPreviousNode();
	void setPreviousNode(Position pos);
	void SearchDis();
	void addHazardPointByPoint(int y, int x);
	void addColorBlobPointByPoint(int y, int x);
private:
	MapNode PreviousNode;
	int mapWidth, mapHeight;
	MapModel *mapModel;
	void AnalyzeMapData();
	int startx, starty;
	void CalAble(int x, int y);
	void SetDisable();
};