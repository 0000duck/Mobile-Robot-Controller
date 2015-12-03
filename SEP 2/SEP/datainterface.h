#include"Common.h"
#include"sensor.h"
#include"robot.h"
#include"mapmanager.h"
class DataInterface
{
public:
	 void Move(int direction);
	 void UseColorSensor(void* result, MapModel mapmodel, Position currentPosition);
	 void UseSensor(int type, void*result, MapModel mapmodel, Position currentPosition); //Colorblob ������ ������ ���� ���
	 SensorSystem sensorSystem;
	 RobotMovementInterface robotMovementInterface;
};