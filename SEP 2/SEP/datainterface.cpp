#include"datainterface.h"

void DataInterface::UseColorSensor(void* result, MapModel *mapmodel, Position currentPosition)
{
	sensorSystem->SensorUse(COLORBLOB_SENSOR, result, mapmodel, currentPosition,2);
}

void DataInterface::UseSensor(int type, void*result, MapModel *mapmodel, Position currentPosition, int direction)
{
	if (type == COLORBLOB_SENSOR)
		UseColorSensor(result, mapmodel, currentPosition);
	else
		sensorSystem->SensorUse(type, result, mapmodel, currentPosition, direction);
}


DataInterface::DataInterface(Position position)
{
	robotMovementInterface = new RobotMovementInterface();
	sensorSystem = new SensorSystem(position);
}