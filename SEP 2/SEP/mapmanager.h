#include"map.h"
class MapManager
{
public:
	int CreateMapModel(int** mapdata);
	int GetNearMapNodeData();
	void AddColorBlob(int colorblobInfo);
	MapNode GetForwardMapNode(Position robotPos, int robotDirection);
	void AddHazardPoint(int hazardInfo);
	int mapWidth, mapHeight;
	MapModel *mapModel;
	MapManager(int** mapInput, int mapX, int mapY, Position Start);
private:
	void AnalyzeMapData();
	int startx, starty;

};