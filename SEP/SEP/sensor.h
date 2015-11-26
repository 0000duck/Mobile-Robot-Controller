

class SensorBase
{
public :
	virtual void Use();

private:

};
class SensorSystem
{
protected:
	const int SensorCount = SENSORNUM;
	SensorBase Sensors[SensorCount];

public:
	void SensorUse();
	SensorSystem();

};

class PositioningSensor : SensorBase
{
public :
	void Use();
	Position position;
};

class ColorSensor : SensorBase
{
public:
	void Use();

private:
	bool IsColorBlobCheck()
	{
		//LOGIC
	}
};

class HazardSensor : SensorBase
{
public :
	void Use();

private:
	bool IsHazardCheck();
};

