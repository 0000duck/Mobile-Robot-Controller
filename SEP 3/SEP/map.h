/*
Map�� ���� �Է���
�켱�� 2���� ������ �Ѵٰ� �����Ѵ�.

*/
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
