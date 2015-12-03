#include "Common.h"
#include"map.h"

#define SENSOR_MAX 10
class SensorBase
{
public :
	SensorBase();
	virtual void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
private:

};

class SensorSystem
{
protected:
	int SensorCount;
	SensorBase* Sensors[SENSOR_MAX];

public:
	void SensorUse(int type, void* result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	SensorSystem();

};


class PositioningSensor : public SensorBase
{
public :
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	Position position;
	void setPosition(int x, int y);
};


class ColorSensor : public SensorBase
{
public:
	void Use(void *result, MapModel *mapmodel, Position currentPosition, int currentDirection);
	ColorSensor();
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

