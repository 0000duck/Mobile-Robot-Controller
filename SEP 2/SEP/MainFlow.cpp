
#include <fstream>
#include <iostream>
#include"moveManager.h"
//paragmaOnce
using namespace std;
MoveManager* moveManager;

void init(int startX, startY, mapHeight, mapWidth, )
{
	static int **GivingMapNode;
	Position startP;
	MapNode mapnode;
	mapnode.position.x = 4;
	mapnode.position.y = 4;
	mapnode.data.kind = EXPLROATIONPOINT;
	mapnode.isDetected = false;
	const unsigned int mapWidth = 21, mapHeight = 28;
	FILE * file;
	file = fopen("map.txt", "r");
	int i, j;
	GivingMapNode = new int*[mapHeight];// (int**)malloc((sizeof(int)*mapWidth*mapHeight));

	for (i = 0; i < mapHeight; i++)
	{
		GivingMapNode[i] = new int[mapWidth];//(int*)malloc((sizeof(int)*mapWidth));
	}



	for (i = 0; i < mapHeight; i++)
	{
		for (j = 0; j < mapWidth; j++)
		{
			fscanf(file, "%d", &GivingMapNode[i][j]);
		}
	}
	startP.x = 20;
	startP.y = 0;
	fclose(file);

	moveManager = new MoveManager(GivingMapNode, startP, mapWidth, mapHeight, mapnode);
}
int main()
{
	
	init();
	moveManager->Explore();
}