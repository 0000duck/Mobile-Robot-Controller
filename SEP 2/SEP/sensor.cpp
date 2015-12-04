#include"Common.h"
#include"global.h"
#include"map.h"
#include "sensor.h"




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

void ColorSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{
	int *temp = (int*)result;
	*temp = 0;
	//int값으로 알려준다.
	//	8
	//4		6
	//	2		 현재방향에서 8426방향을 스캔하면서 8426 순서로 COLORBLOB이면 1아니면0을 표시
	// 842 는 coloblob이고 6은 아니라면 0x1110

	if (mapmodel->Map[currentPosition.y + 1][currentPosition.x].data.kind == COLORBLOB)
			*temp |= 0x0010;
	if ((currentPosition.y>0)&&(mapmodel->Map[currentPosition.y - 1][currentPosition.x].data.kind == COLORBLOB))
			*temp |= 0x1000;
	if (mapmodel->Map[currentPosition.y][currentPosition.x + 1].data.kind == COLORBLOB)
			*temp |= 0x0001;
	if ((currentPosition.x>0) && (mapmodel->Map[currentPosition.y][currentPosition.x - 1].data.kind == COLORBLOB))
			*temp |= 0x0100;

}

void HazardSensor::Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)
{
	int *temp = (int*)result;
	*temp = 0;
	
	switch (currentDirection)
	{
	case 2:
		if (mapmodel->Map[currentPosition.y + 1][currentPosition.x].data.kind == HAZARD)
			*temp |= 0x0010;
		break;
	case 8:
		if ((currentPosition.y>0)&&(mapmodel->Map[currentPosition.y - 1][currentPosition.x].data.kind == HAZARD))
			*temp |= 0x1000;
		break;
	case 6:
		if (mapmodel->Map[currentPosition.y][currentPosition.x + 1].data.kind == HAZARD)
			*temp |= 0x0001;
		break;
	case 4:
	if ((currentPosition.x>0)&&(mapmodel->Map[currentPosition.y][currentPosition.x - 1].data.kind == HAZARD))
			*temp |= 0x0100;
		break;
	}
	
}
