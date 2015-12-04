#pragma once
#include"Common.h"
#include"map.h"
class SensorBase
{
public :
	virtual void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection)=0;
private:

};

class SensorSystem
{
protected:
	int SensorCount;

public:
	SensorBase* Sensors[SENSOR_MAX];
	void SensorUse(int type, void* result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	SensorSystem(Position position);
};


class PositioningSensor : public SensorBase
{
public :
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	Position position;
	PositioningSensor(Position c);
	void SetPosition(Position p);
};


class ColorSensor : public SensorBase
{
public:
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
private:
	
	bool IsColorBlobCheck();
	
};


class HazardSensor : public SensorBase
{
public :
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);

private:
	bool IsHazardCheck();
};
