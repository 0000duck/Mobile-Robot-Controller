#pragma once
#define INIT 0
#define SENSORNUM 3
#define HAZARD 5
#define COLORBLOB 6
#define NORMAL 7
#define EXPLROATIONPOINT 8
#define WALL	9
#define POSSIBLEDIRECTION 4	//로봇이 바라볼 수 있는 방향

#define COLORBLOB_SENSOR 11
#define HAZARD_SENSOR 12
#define POSITIONING_SENSOR 13

#define POSITIONING_ERROR 44
#define SENSOR_MAX 3

typedef struct Position
{
	int x;
	int y;
}Position;




