/*
Map�� ���� �Է���
�켱�� 2���� ������ �Ѵٰ� �����Ѵ�.

*/
#pragma once
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
	MapModel(int width, int height);
	MapNode** Map;
};
