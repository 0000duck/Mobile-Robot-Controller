#include"Common.h"
#include"global.h"
#include"map.h"


class MapModel
{
private:

public:
	MapModel();
	MapNode Map[mapHeight][mapWidth];
};




//실제 맵이 아닌 입력받은 가상 맵
MapModel::MapModel()//Map을 입력받고 초기화
{

}

