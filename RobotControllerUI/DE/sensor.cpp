#include"Common.h"
#include"global.h"
#include"map.h"
#include "sensor.h"

using namespace std;


SensorSystem::SensorSystem(Position position)
{
	SensorCount = SENSORNUM;
	Sensors[0] = new ColorSensor();
	Sensors[1] = new HazardSensor();
	Sensors[2] = new PositioningSensor(position);
}

void SensorSystem::SensorUse(int type, void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{
	switch (type)
	{
	case COLORBLOB_SENSOR:
		Sensors[0]->Use(result, mapmodel, currentPosition, currentDirection);
		break;
	case HAZARD_SENSOR:
		Sensors[1]->Use(result, mapmodel, currentPosition, currentDirection);
		break;
	case POSITIONING_SENSOR:
		Sensors[2]->Use(result, mapmodel, currentPosition, currentDirection);
		break;

	}
}



void PositioningSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{
	Position *temp = ((Position*)result);
	temp->x = position.x;
	temp->y = position.y;

}

PositioningSensor::PositioningSensor(Position c)
{
	position.x = c.x;
	position.y = c.y;

}
void PositioningSensor::SetPosition(Position p)
{
	position = p;
}

Position PositioningSensor::GetPosition()
{
	return position;
}

int ColorSensor::generator(){
	return ran.get();
}
void ColorSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{

	MapNode ** Map = mapmodel->getMapNode();
	int *temp = (int*)result;
	*temp = 0;
	int x = currentPosition.x, y = currentPosition.y;
	//colorblob ���� ����
	//srand(time(NULL));

	if (x > 0 && x < mapmodel->getMapWidth() - 1 && y>0 && y < mapmodel->getMapHeight() - 1) {

		if (Map[y - 1][x].isDetected == false) {
			Map[y - 1][x].isDetected = true;
			if (generator() < 20 && Map[y - 1][x].data.kind == NORMAL) {
				*temp |= DOWN;
			}
		}

		if (Map[y][x - 1].isDetected == false) {
			Map[y][x - 1].isDetected = true;
			if (generator() < 20 && Map[y][x - 1].data.kind == NORMAL) {
				*temp |= LEFT;
			}
		}

		if (Map[y + 1][x].isDetected == false) {
			Map[y + 1][x].isDetected = true;
			if (generator() < 20 && Map[y + 1][x].data.kind == NORMAL) {
				*temp |= UP;
			}
		}

		if (Map[y][x + 1].isDetected == false) {
			Map[y][x + 1].isDetected = true;
			if (generator()< 20 && Map[y][x + 1].data.kind == NORMAL) {
				*temp |= RIGHT;
			}
		}
	}

}


int HazardSensor::generator(){
	return ran.get();
}
void HazardSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{

	MapNode ** Map = mapmodel->getMapNode();
	int *temp = (int*)result;
	*temp = 0;
	int x = currentPosition.x, y = currentPosition.y;
	//srand(time(NULL));
	//colorblob ���� ����




	//int������ �˷��ش�.
	//	8
	//4		6
	//	2		 ������⿡�� 8426������ ��ĵ�ϸ鼭 8426 ������ COLORBLOB�̸� 1�ƴϸ�0�� ǥ��
	// 842 �� coloblob�̰� 6�� �ƴ϶�� 0x1110

	
	if ((x > 0) && (x < mapmodel->getMapWidth() - 1 )&&( y>0) && (y < mapmodel->getMapHeight() - 1)){
		switch (currentDirection)
		{
		case UP:
			if (Map[y + 1][x].isDetected == false){
				Map[y + 1][x].isDetected = true;
				if (generator()<10&& Map[y + 1][x].data.kind == NORMAL){
					*temp |= UP;
				}
			}
			break;

		case LEFT:
			if (Map[y ][x - 1].isDetected == false){
					Map[y ][x - 1].isDetected = true;
				if (generator() < 10 && Map[y][x - 1].data.kind == NORMAL){
					*temp |= LEFT;
				}
			}
			break;

		case DOWN:
			if (Map[y - 1][x].isDetected == false){
					Map[y - 1][x].isDetected = true;
				if (generator() < 10 && Map[y - 1][x].data.kind == NORMAL){
					*temp |= DOWN;
				}
			}
			break;
		case RIGHT:
			if (Map[y][x + 1].isDetected == false){
					Map[y][x + 1].isDetected = true;
				if (generator()< 10 && Map[y][x + 1].data.kind == NORMAL){
					*temp |= RIGHT;
				}
			}
			break;
		}
	}
	
	
}
