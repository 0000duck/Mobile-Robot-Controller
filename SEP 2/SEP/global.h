
#include"robot.h"
#include"mapmanager.h"
#include"VirtualRobot.h"
#include "Common.h"
#include"map.h"
#include"sensor.h"

//����, �κ�, ����κ�, ������ ��� �۷ι��� �̸� �����Ѵ�.(������� ����)

int rotateDirection[POSSIBLEDIRECTION] = { 8, 4, 2, 6 };

const unsigned int mapWidth = 30, mapHeight = 30;
Position startP;
//int **mapInput;
//������� ��������
Position CurrentPosition;//��� robot�� ������ ������, ������ �� ����
						//������ ���� global�� �����°� �����ϴٰ� �Ǵ��Ͽ� ��
int **GivingMapNode;		//���� ����
/*
map
0,0		1,0

0,1		1,1
*///	��������
//������� ���� ����


//������� ���� ����
Position VirtualPosition;
//���� ���� MapModel�� ������ ����
VirtualRobot virtualRobot;




//���� ���� ��
SensorSystem sensor;