#include<map.h>

class moveManager
{
public:
	List<mapNode> SeachSpotList[];
	List<mapNode> RemainSearchSpotList[];
	void InitializeMoveData();
	void AnalyzeSensingData();
	int CompareCurrentPos();
	void MakeNextMoveDate();
	void GetNextMoveDate();
	void GetPositioningSensorDate();
private:
	bool CheckMoveDataInvalid();
	void Explore();
	void GetMapModel();
	void AnalyzePositioningSensorData();
	void AnalyzeColorSensorDate();
	void AnalyzeHazardSensor();

};