#include"map.h"
#include"datainterface.h"
#include"mapmanager.h"
#include<list>
using namespace std;
class MoveManager
{
public:
	list<MapNode> SearchSpotList;
	list<MapNode> RemainSearchSpotList;
	void InitializeMoveData();
	void AnalyzeSensingData();
	int CompareCurrentPos();
	void MakeNextMoveData();
	void GetNextMoveData();
	void GetPositioningSensorData(void *result);

	MoveManager(int** mpaInput);
	DataInterface dataInterface;
	MapManager mapManager;
	VirtualRobot virtualRobot;
private:
	bool CheckMoveDataInvalid();
	void Explore();
	void GetMapModel(int** mpaInput);
	void AnalyzePositioningSensorData();
	void AnalyzeColorSensorData();
	void AnalyzeHazardSensorData();//¿Ã∏ß πŸ≤ﬁ
};