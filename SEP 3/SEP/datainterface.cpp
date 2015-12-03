#include"datainterface.h"

void DataInterface::UseColorSensor(void* result)
{
	sensorSystem.SensorUse(COLORBLOB_SENSOR, result);
}

void DataInterface::UseSensor(int type, void*result)
{
	if (type == COLORBLOB_SENSOR)
		UseColorSensor(result);
	else
		sensorSystem.SensorUse(type, result);
}

void DataInterface::Move(int direction)
{
	robotMovementInterface.MoveRequest(direction);
}
