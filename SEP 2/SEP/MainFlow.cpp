#include <fstream>
#include <iostream>
#include"moveManager.h"
//paragmaOnce
using namespace std;
int main()
{
	MapNode mapnode ;
	mapnode.PosX = 3;
	mapnode.PosY = 3;
	mapnode.data.kind = EXPLROATIONPOINT;
	mapnode.isDetected = false;
	const unsigned int mapWidth = 5, mapHeight = 5;
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
			printf("%d", GivingMapNode[i][j]);
		}
		printf("\n");
	}
	startP.x = 0;
	startP.y = 0;
	fclose(file);
	
	MoveManager moveManager(GivingMapNode, startP,mapWidth,mapHeight, mapnode);
	
	moveManager.Explore();
}