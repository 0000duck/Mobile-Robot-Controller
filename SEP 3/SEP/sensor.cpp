#include "sensor.h"
#include"global.h"
void PositioningSensor::Use(void *result)
{
	Position *temp = ((Position*)result);
	temp->x = CurrentPosition.x;
	temp->y = CurrentPosition.y;
	//고쳐야된다
}

void ColorSensor::Use(void *result)
{
	int *temp = (int*)result;
	*temp = 0;
	//int값으로 알려준다.
	//	8
	//4		6
	//	2		 현재방향에서 8426방향을 스캔하면서 8426 순서로 COLORBLOB이면 1아니면0을 표시
	// 842 는 coloblob이고 6은 아니라면 0x1110
	if (RealMapNode[CurrentPosition.x][CurrentPosition.y + 1].data.kind == COLORBLOB);
		*temp |= 0x0010;
	if (RealMapNode[CurrentPosition.x][CurrentPosition.y - 1].data.kind == COLORBLOB);
		*temp |= 0x1000;
	if (RealMapNode[CurrentPosition.x + 1][CurrentPosition.y].data.kind == COLORBLOB);
		*temp |= 0x0001;
	if (RealMapNode[CurrentPosition.x - 1][CurrentPosition.y].data.kind == COLORBLOB);
		*temp |= 0x0100;

}

void HazardSensor::Use(void *result)
{
	int *temp = (int*)result;
	*temp = 0;
	//위의 colorblob방식과 동일
	//지금은 귀찮아서 전방향으로 했는데 바꿔야됨
	if (RealMapNode[CurrentPosition.x][CurrentPosition.y + 1].data.kind == HAZARD);
		*temp |= 0x0010;
	if (RealMapNode[CurrentPosition.x][CurrentPosition.y - 1].data.kind == HAZARD);
		*temp |= 0x1000;
	if (RealMapNode[CurrentPosition.x + 1][CurrentPosition.y].data.kind == HAZARD);
		*temp |= 0x0001;
	if (RealMapNode[CurrentPosition.x - 1][CurrentPosition.y].data.kind == HAZARD);
		*temp |= 0x0100;
	
}

SensorSystem::SensorSystem()
{
	//일반화가 힘듭니다.
	Sensors[0] = new ColorSensor();
	Sensors[1] = new HazardSensor();
	Sensors[2] = new PositioningSensor(); 
}

void SensorSystem::SensorUse(int type, void *result)
{
	switch (type)
	{
	case COLORBLOB_SENSOR:
		Sensors[0].Use(result);
		break;
	case HAZARD_SENSOR:
		Sensors[1].Use(result);
		break;
	case POSITIONING_SENSOR:
		Sensors[2].Use(result);
		break;

	}
}
