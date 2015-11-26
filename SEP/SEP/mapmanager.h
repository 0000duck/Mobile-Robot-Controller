
class MapManager
{
public:
	int CreateMapModel();
	int GetNearMapNodeData();
	int AddColorBlob();
	int GetForwardMapNode();
	int AddHazardPoint();
private:
	void AnalyzeMapData();
}