#include"Common.h"
#include"sensor.h"
#include"robot.h"
class DataInterface
{
public:
	 void Move(int direction);
	 void UseColorSensor(void* result);
	 void UseSensor(int type, void*result); //Colorblob ������ ������ ���� ���
	 SensorSystem sensorSystem;
	 RobotMovementInterface robotMovementInterface;
};