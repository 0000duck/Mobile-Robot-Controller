
class DataObject
{
public:
	int kind;
};

class MapNode
{
protected :
	bool isDetected;
	int PosX,PosY;
};

class MapModel
{
private:
	MapNode NotedNodeList[];
};
