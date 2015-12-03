#include "sensor.h"
#include"global.h"
void PositioningSensor::Use(void *result)
{
	Position *temp = ((Position*)result);
	temp->x = CurrentPosition.x;
	temp->y = CurrentPosition.y;
	//���ľߵȴ�
}

void ColorSensor::Use(void *result)
{
	int *temp = (int*)result;
	*temp = 0;
	//int������ �˷��ش�.
	//	8
	//4		6
	//	2		 ������⿡�� 8426������ ��ĵ�ϸ鼭 8426 ������ COLORBLOB�̸� 1�ƴϸ�0�� ǥ��
	// 842 �� coloblob�̰� 6�� �ƴ϶�� 0x1110
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
	//���� colorblob��İ� ����
	//������ �����Ƽ� ���������� �ߴµ� �ٲ�ߵ�
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
	//�Ϲ�ȭ�� ����ϴ�.
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
