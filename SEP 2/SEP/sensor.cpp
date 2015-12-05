#include <random>
#include <ctime>
#include <iostream>
#include <functional>
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

void ColorSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{
	mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	uniform_int_distribution<int> distribution(0, 100);       // 생성 범위
	auto generator = bind(distribution, engine);
	MapNode ** Map = mapmodel->getMapNode();
	int *temp = (int*)result;
	*temp = 0;
	int x = currentPosition.x , y = currentPosition.y;
	//colorblob 랜덤 생성


	//int값으로 알려준다.
	//	8
	//4		6
	//	2		 현재방향에서 8426방향을 스캔하면서 8426 순서로 COLORBLOB이면 1아니면0을 표시
	// 842 는 coloblob이고 6은 아니라면 0x1110
	/*
	if (Map[currentPosition.y + 1][currentPosition.x].data.kind == COLORBLOB)
			*temp |= 0x0010;
	if ((currentPosition.y>0)&&(Map[currentPosition.y - 1][currentPosition.x].data.kind == COLORBLOB))
			*temp |= 0x1000;
	if (Map[currentPosition.y][currentPosition.x + 1].data.kind == COLORBLOB)
			*temp |= 0x0001;
	if ((currentPosition.x>0) && (Map[currentPosition.y][currentPosition.x - 1].data.kind == COLORBLOB))
			*temp |= 0x0100;
			*/
	if (x > 0 && x < mapmodel->getMapWidth() - 1 && y>0 && y < mapmodel->getMapHeight() - 1){
		if ((generator() < 10) && Map[currentPosition.y + 1][currentPosition.x].data.kind == NORMAL)
			*temp |= 0x0010;
		if (generator() < 10 && Map[currentPosition.y - 1][currentPosition.x].data.kind == NORMAL)
			*temp |= 0x1000;
		if (generator() < 10 && Map[currentPosition.y ][currentPosition.x + 1].data.kind == NORMAL)
			*temp |= 0x0001;
		if (generator() < 10 && Map[currentPosition.y ][currentPosition.x -1 ].data.kind == NORMAL)
			*temp |= 0x0100;
	}
}

void HazardSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{
	mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	uniform_int_distribution<int> distribution(0, 100);       // 생성 범위
	auto generator = bind(distribution, engine);
	MapNode ** Map = mapmodel->getMapNode();
	int *temp = (int*)result;
	*temp = 0;
	int x = currentPosition.x, y = currentPosition.y;
	//colorblob 랜덤 생성


	//int값으로 알려준다.
	//	8
	//4		6
	//	2		 현재방향에서 8426방향을 스캔하면서 8426 순서로 COLORBLOB이면 1아니면0을 표시
	// 842 는 coloblob이고 6은 아니라면 0x1110
	/*
	if (Map[currentPosition.y + 1][currentPosition.x].data.kind == COLORBLOB)
	*temp |= 0x0010;
	if ((currentPosition.y>0)&&(Map[currentPosition.y - 1][currentPosition.x].data.kind == COLORBLOB))
	*temp |= 0x1000;
	if (Map[currentPosition.y][currentPosition.x + 1].data.kind == COLORBLOB)
	*temp |= 0x0001;
	if ((currentPosition.x>0) && (Map[currentPosition.y][currentPosition.x - 1].data.kind == COLORBLOB))
	*temp |= 0x0100;
	*/if (x > 0 && x < mapmodel->getMapWidth() - 1 && y>0 && y < mapmodel->getMapHeight() - 1){
		switch (currentDirection)
		{
		case 8:
			if (Map[currentPosition.y - 1][currentPosition.x].isDetected == false){
				if (generator() < 20&&Map[currentPosition.y - 1][currentPosition.x].data.kind == NORMAL){
					Map[currentPosition.y - 1][currentPosition.x].isDetected = true;
					*temp |= 0x1000;
				}
			}
			break;

		case 4:
			if (Map[currentPosition.y ][currentPosition.x - 1].isDetected == false){
				if (generator() < 20 && Map[currentPosition.y ][currentPosition.x - 1].data.kind == NORMAL){
					Map[currentPosition.y ][currentPosition.x - 1].isDetected = true;
					*temp |= 0x0100;
				}
			}
			break;

		case 2:
			if (Map[currentPosition.y + 1][currentPosition.x].isDetected == false){
				if (generator() < 20 && Map[currentPosition.y + 1][currentPosition.x].data.kind == NORMAL){
					Map[currentPosition.y + 1][currentPosition.x].isDetected = true;
					*temp |= 0x0010;
				}
			}
			break;
		case 6:
			if (Map[currentPosition.y][currentPosition.x + 1].isDetected == false){
				if (generator() < 20 && Map[currentPosition.y][currentPosition.x + 1].data.kind == NORMAL){
					Map[currentPosition.y][currentPosition.x + 1].isDetected = true;
					*temp |= 0x0001;
				}
			}
			break;
		}
	}
}
