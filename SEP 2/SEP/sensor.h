#include "Common.h"

class SensorBase
{
public :
	virtual void Use(void *result);

private:

};
class SensorSystem
{
protected:
	const int SensorCount = SENSORNUM;
	SensorBase Sensors[SensorCount];

public:
	void SensorUse(int type, void* result, MapModel mapmodel, Position currentPosition);
	SensorSystem();

};


class PositioningSensor : SensorBase
{
public :
	void Use(void *result, MapModel mapmodel, Position currentPosition);
	Position position;
};


class ColorSensor : SensorBase
{
public:
	void Use(void *result, MapModel mapmodel, Position currentPosition);

private:
	bool IsColorBlobCheck()
	{
		//LOGIC
	}
};


class HazardSensor : SensorBase
{
public :
	void Use(void *result, MapModel mapmodel, Position currentPosition);

private:
	bool IsHazardCheck();
};

