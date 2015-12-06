#pragma once
#define INIT 0
#define SENSORNUM 3
#define HAZARD 5
#define COLORBLOB 6
#define NORMAL 7
#define EXPLROATIONPOINT 8
#define WALL	9
#define POSSIBLEDIRECTION 4	//�κ��� �ٶ� �� �ִ� ����
#define DIS 1
#define COLORBLOB_SENSOR 11
#define HAZARD_SENSOR 12
#define POSITIONING_SENSOR 13

#define POSITIONING_ERROR 44
#define SENSOR_MAX 3

#define UP 0x1000
#define DOWN 0x0010
#define LEFT 0x0100
#define RIGHT 0x0001

typedef struct Position
{
	int x;
	int y;
}Position;




