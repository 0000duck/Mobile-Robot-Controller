#include"moveManager.h"
#include"global.h"
#include<stdio.h>
//paragmaOnce
int main()
{
	int i, j;
	GivingMapNode = (int**)malloc((sizeof(int)*mapWidth*mapHeight));

	for (i = 0; i < mapHeight; i++)
	{
		GivingMapNode[i] = (int*)malloc((sizeof(int)*mapWidth));
	}
	startP.x = 0;
	startP.y = 0;
	startP.direction = 2;

	//RealMapNode[1][1] = 5;
	MoveManager moveManager(GivingMapNode, startP);
	
	moveManager.Explore();
}