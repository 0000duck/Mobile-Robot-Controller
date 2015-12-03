#include"Common.h"
#include"sensor.h"
#include"robot.h"
class DataInterface
{
public:
	 void Move(int direction);
	 void UseColorSensor(void* result);
	 void UseSensor(int type, void*result); //Colorblob 센서를 제외한 것을 사용
	 SensorSystem sensorSystem;
	 RobotMovementInterface robotMovementInterface;
};