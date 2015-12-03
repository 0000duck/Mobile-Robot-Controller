/*
Map에 대한 입력은
우선은 2차원 수열로 한다고 가정한다.

*/

class DataObject
{
public:
	int kind;
};

class MapNode
{
public :
	bool isDetected;
	int PosX, PosY;
	DataObject data;
protected:
	
};

class MapModel
{
private:
	
public:
	MapModel();
	MapNode Map[mapHeight][mapWidth];
};
