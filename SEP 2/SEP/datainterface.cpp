
#include"datainterface.h"
DataInterface::DataInterface(Position position,int direction)
{
	robotMovementInterface = new RobotMovementInterface(position, direction);
	sensorSystem = new SensorSystem(position);
}

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

Position DataInterface::getRobotPosition()
{
	return robotMovementInterface->getRobotPosition();
}

int DataInterface::getRobotDirection()
{
	return robotMovementInterface->getRobotDirection();
}

void DataInterface::requestRobotMove()
{
	robotMovementInterface->MoveRequest();
}
void DataInterface::requestRobotRotate(int direction)
{
	robotMovementInterface->RotateRequest(direction);
}