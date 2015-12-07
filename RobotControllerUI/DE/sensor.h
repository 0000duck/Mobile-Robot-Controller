#pragma once
#include"Common.h"
#include"map.h"
#include"global.h"
class SensorBase
{
public :
	virtual void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)=0;
private:

};

class SensorSystem
{
protected:
	int SensorCount;//필요한가
public:
	void SensorUse(int type, void* result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	SensorSystem(Position position);
	SensorBase* Sensors[SENSOR_MAX];
private:
};


class PositioningSensor : public SensorBase
{
public :
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	PositioningSensor(Position c);
	void SetPosition(Position p);
	Position GetPosition();
private:
	Position position;
};


class ColorSensor : public SensorBase
{
public:
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	bool IsColorBlobCheck();
	int generator();
	Ran ran;
private:
	
};


class HazardSensor : public SensorBase
{
public :
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	bool IsHazardCheck();
	int generator();
	Ran ran;
private:
};

