
class MapManager
{
public:
	int CreateMapModel(int** mapdata);
	int GetNearMapNodeData();
	void AddColorBlob(int colorblobInfo);
	int GetForwardMapNode();
	void AddHazardPoint(int hazardInfo);
	int mapWidth, mapHeight;
	MapModel mapModel;
private:
	void AnalyzeMapData();

};