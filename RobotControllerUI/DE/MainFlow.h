#pragma once


class MovementInterface
{
public:
	MovementInterface();
	void init(int startY, int startX, int mapHeight, int mapWidth);

	void AddHazardPoint(int y, int x);
	void AddColorBlobPoint(int y, int x);
	void move();
	void addExplorationPoint(int y, int x);
	void start();

};