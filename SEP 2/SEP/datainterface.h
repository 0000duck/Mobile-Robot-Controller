#pragma once
#include"map.h"
#include"sensor.h"
#include"robot.h"
class DataInterface
{
public:

	 void UseColorSensor(void* result, MapModel *mapmodel, Position currentPosition);
	 void UseSensor(int type, void*result, MapModel *mapmodel, Position currentPosition, int direction); //Colorblob 센서를 제외한 것을 사용
	 SensorSystem* sensorSystem;
	 RobotMovementInterface* robotMovementInterface;
	 DataInterface(Position position);
};