#include"moveManager.h"
#include"global.h"
#include<stdio.h>
int main()
{
	int i, j;
	RealMapNode = (int**)malloc((sizeof(int)*mapWidth*mapHeight));

	for (i = 0; i < mapHeight; i++)
	{
		RealMapNode[i] = (int*)malloc((sizeof(int)*mapWidth));
	}
	//RealMapNode[1][1] = 5;
	MoveManager moveManager(RealMapNode, startP);
	
	moveManager.Explore();
}