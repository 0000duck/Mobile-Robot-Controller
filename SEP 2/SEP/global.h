
#include"robot.h"
#include"mapmanager.h"
#include"VirtualRobot.h"
#include "Common.h"
#include"map.h"
#include"sensor.h"

//센서, 로봇, 가상로봇, 실제맵 모두 글로벌로 미리 선언한다.(가상맵은 제외)

int rotateDirection[POSSIBLEDIRECTION] = { 8, 4, 2, 6 };

const unsigned int mapWidth = 30, mapHeight = 30;
Position startP;
//int **mapInput;
//여기부터 실제정보
Position CurrentPosition;//비록 robot이 가지고 있지만, 센서가 이 값을
						//가지는 것은 global로 가지는게 적절하다고 판단하여 함
int **GivingMapNode;		//실제 지도
/*
map
0,0		1,0

0,1		1,1
*///	지도형식
//여기까지 실제 정보


//여기부터 가상 정보
Position VirtualPosition;
//가상 맵은 MapModel이 가지고 있음
VirtualRobot virtualRobot;




//가상 정보 끝
SensorSystem sensor;