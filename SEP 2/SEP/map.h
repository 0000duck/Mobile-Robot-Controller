/*
Map�� ���� �Է���
�켱�� 2���� ������ �Ѵٰ� �����Ѵ�.

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
